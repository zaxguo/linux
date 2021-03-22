#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <errno.h>


#define DEFAULT_FS_CNT			4
#define MAX_RECORDS				8000
#define BILLION					1E9
#define READ_BUF_SIZE			90000

char *files[5] = {
	"mail_index/snapshot1.json",
	"mail_index/schema_1.json",
	"mail_index/seg_1/cfmeta.json",
	"mail_index/seg_1/segmeta.json",
	"mail_index/seg_1/cf.dat"
};

__thread int fd_open_table[] = {0, 0, 0, 0, 0};


struct args {
	int tid;
	char *data;
	char *buf;
};

/* r/w only */
struct syscall {
	int fd;
	int size;
	int offset;
};

struct trace_lib {
	struct syscall *head[MAX_RECORDS]; /* point to the first */
	int cnt;
};

struct trace_lib lib = {
	.head = NULL,
	.cnt = 0,
};

int fs_cnt = DEFAULT_FS_CNT;

static struct syscall *get_trace_from_lib(int idx) {
	return lib.head[idx];
}

static int file_opened(int fd) {
	return fd_open_table[fd] == 0;
}

static void set_file_opened(int file, int fd) {
	fd_open_table[file] = fd;
	return;
}

static int get_open_fd(int fd) {
	return fd_open_table[fd];
}



static void *replay(void *args) {
	int ret, total, txt, idx;
	char dest[100];
	struct args *arg = (struct args*) args;
	struct timespec start, end;
	double delta;
	if (arg->tid == 0) {
		clock_gettime(CLOCK_MONOTONIC, &start);
	}
	total = 0;
	idx = 0;
	do {
		struct syscall *call = get_trace_from_lib(idx++);
		if (file_opened(call->fd)) {
			ret = snprintf(dest, 100, "/sybil/fs%d/%s", arg->tid, files[call->fd]);
			txt = open(dest, O_RDWR);
			if (txt > 0) {
				/* set fd to the opened file */
				set_file_opened(call->fd, txt);
				/*printf("opening %s\n", dest);*/
			} else {
				printf("fail to open %s, ret = %d\n", dest, txt);
				exit(EXIT_FAILURE);
			}
		} else {
			txt = get_open_fd(call->fd);
			/*printf("[%d]:open %s on %d\n", arg->tid, files[call->fd], txt);*/
		}
		ret = pread(txt, arg->buf, call->size, call->offset);
		if (ret > 0) {
			total += ret;
		}
	} while(idx < lib.cnt);
	if (arg->tid == 0) {
		clock_gettime(CLOCK_MONOTONIC, &end);
		delta = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/BILLION;
		printf("[%d]: takes %f seconds for actual to finish.\n", fs_cnt, delta);
	}
	printf("[%d]:replayed %d ops: rw %d bytes to %s.\n", arg->tid, idx, total, dest);
}

static int construct_lib(char *lib_path) {
	FILE *trace_file;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int lib_idx = 0;
	trace_file = fopen(lib_path, "r");
	if (trace_file == NULL) {
		perror("fopen");
		printf("cannot open trace file!\n");
		exit(EXIT_FAILURE);
	}
	while (((nread = getline(&line, &len, trace_file)) != -1) && lib_idx < MAX_RECORDS) {
		int cnt, idx, res, j;
		cnt = 0; idx = 0;
		struct syscall *call = malloc(sizeof(struct syscall));
		while (idx < strlen(line)) {
			if (line[idx++] == ',') {
				if (cnt == 0) {
					int tmp;
					for (tmp = 0; tmp < 5; tmp++) {
						if (!strncmp(line, files[tmp], idx-1)) {
							call->fd = tmp;
							break;
						}
					}
					j = idx;
				} else if (cnt == 1) {
					call->size = atoi(line + j);
					call->offset = atoi(line + idx);
					if (call->size > READ_BUF_SIZE) {
						printf("%d: enlarge read buf size to at least %d\n", __LINE__, call->size);
						exit(EXIT_FAILURE);
					}
				}
				cnt++;
			}
		}
		j = 0;
		/*printf("call fd = %d, size = %d, offset = %d\n", call->fd, call->size, call->offset);*/
		lib.head[lib_idx++] = call;
	}
	lib.cnt = lib_idx;
	free(line);
	fclose(trace_file);
	return 0;
}


static int create_file_of_size(int fs, const char *path, unsigned long file_size) {
	char dest[100];
	char *data;
	int ret, size, txt, cnt;
	unsigned long total;
	/* email db size */
	unsigned long db_size = file_size;
	total = 0;
	size = 40960;
	if (db_size < size) {
		size = db_size;
	}
	data = malloc(50000);
	memset(data, 'a', size);
	cnt = 0;
	ret = snprintf(dest, 100, "/sybil/fs%d/%s", fs, path);
	txt = open(dest, O_RDWR);
	if (!txt) {
		printf("fail to open %s!\n", dest);
		return 0;
	}
	do {
		ret = write(txt, data, size);
		if (ret) {
			total += ret;
		}
		if ((cnt % 256) == 0) {
			/*printf("%d MB...\n", (int)(total >> 20));*/
			fsync(txt);
		}
		++cnt;
	} while ((ret == size) && (total < db_size));
	printf("creating %ld bytes to %s\n", total, dest);
	close(txt);
	free(data);
	return 0;
}

int main(int argc, char *argv[]) {
	int i, ret;
	pthread_t tid, actual;
	char *data, *trace_path;
	if (argc == 3) {
		fs_cnt = atoi(argv[1]);
		trace_path = argv[2];
		printf("traces replay on %d fses..lib path = %s\n", fs_cnt, trace_path);
	} else {
		printf("plz supply correct arguments!\n");
		exit(0);
	}
	ret = open(trace_path, O_RDONLY);
	if (ret < 0) {
		printf("setting up db files for %d..\n", fs_cnt);
		ret = create_file_of_size(fs_cnt, "mail_index/snapshot1.json", 93);
		ret = create_file_of_size(fs_cnt, "mail_index/schema_1.json", 242);
		ret = create_file_of_size(fs_cnt, "mail_index/seg_1/cfmeta.json", 804);
		ret = create_file_of_size(fs_cnt, "mail_index/seg_1/segmeta.json", 400);
		ret = create_file_of_size(fs_cnt, "mail_index/seg_1/cf.dat", 2032423728);
		return 0;
	} else {
		printf("Kicking off the exp...\n");
		ret = construct_lib(trace_path);
		/* prepare the data buffer */
		for (i = 0; i < fs_cnt; i++) {
			struct args* arg = malloc(sizeof(struct args));
			/* read buffer */
			char *buf = malloc(READ_BUF_SIZE);
			arg->tid = i;
			arg->data = NULL;
			arg->buf = buf;
			ret = pthread_create(&tid, NULL, replay, (void *)arg);
			if (i == 0) {
				actual = tid;
			}
		}
		/* wait for the actual to finish */
		pthread_join(actual, NULL);
		/*pthread_join(actual, NULL);*/
		pthread_exit(0);
	}
	return 0;
}
