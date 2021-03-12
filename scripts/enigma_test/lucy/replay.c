#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define DEFAULT_FS_CNT			4
#define MAX_RECORDS				8000
#define BILLION					1E9

struct args {
	int tid;
	char *data;
	char *buf;
};

/* r/w only */
struct syscall {
	int op;
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

static void *replay(void *args) {
	int ret, size, total, txt, idx;
	char dest[50];
	struct args *arg = (struct args*) args;
	struct timespec start, end;
	double delta;
	if (arg->tid == 0) {
		clock_gettime(CLOCK_MONOTONIC, &start);
	}
	total = 0;
	idx = 0;
	ret = snprintf(dest, 50, "/sybil/fs%d/test.txt", arg->tid);
	txt = open(dest, O_RDWR);
	do {
		struct syscall *call = get_trace_from_lib(idx++);
		switch (call->op) {
			case 0:
				ret = pread(txt, arg->buf, call->size, call->offset);
				break;
			case 1:
				ret = pwrite(txt, arg->data, call->size, call->offset);
				break;
		}
		if (ret > 0) {
			total += ret;
		}
		/*printf("[%d]:ret = %d, write_size = %d\n", arg->tid, ret, write_size);*/
	} while(idx < lib.cnt);
	fsync(txt);
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
	/*lib = malloc(MAX_RECORDS * sizeof(struct syscall *));*/
	if (trace_file == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	while (((nread = getline(&line, &len, trace_file)) != -1) && lib_idx < MAX_RECORDS) {
		int cnt, idx, res, j;
		cnt = 0; idx = 0;
		struct syscall *call = malloc(sizeof(struct syscall));
		while (idx < strlen(line)) {
			if (line[idx++] == ',') {
				if (cnt == 0) {
					call->op = atoi(line);
					j = idx;
				} else if (cnt == 1) {
					call->size = atoi(line + j);
					call->offset = atoi(line + idx);
				}
				cnt++;
			}
		}
		j = 0;
		lib.head[lib_idx++] = call;
	}
	lib.cnt = lib_idx;
	free(line);
	fclose(trace_file);
	return 0;
}

static int setup_db(int fs) {
	char dest[50];
	char *data;
	int ret, size, txt;
	unsigned long total;
	total = 0;
	size = 4096;
	data = malloc(5000);
	memset(data, 'a', size);
	ret = snprintf(dest, 50, "/sybil/fs%d/cf.dat", fs);
	txt = open(dest, O_RDWR);
	do {
		ret = write(txt, data, size);
		if (ret) {
			total += ret;
		}
	} while (ret == size);
	printf("dumping %ld bytes to sbily fs %d\n", total, fs);
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
	/*ret = construct_lib(trace_path);*/
	ret = setup_db(1);
	return 0;
	/* prepare the data buffer */
	data = malloc(9000);
	memset(data, 'a', 9000);
	for (i = 0; i < fs_cnt; i++) {
		struct args* arg = malloc(sizeof(struct args));
		/* read buffer */
		char *buf = malloc(9000);
		arg->tid = i;
		arg->data = data;
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
	return 0;
}
