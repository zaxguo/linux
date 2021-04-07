#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define DEFAULT_FS_CNT			4
#define MAX_RECORDS				8000
#define BILLION					1E9

struct args {
	int tid;
	char *data;
	char *buf;
};

int fs_cnt = DEFAULT_FS_CNT;

static void *replay(void *args) {
	int ret, size, total, txt, idx;
	char dest[50];
	struct args *arg = (struct args*) args;
	struct timespec start, end;
	double delta;
	struct stat sb;
	if (arg->tid == 0) {
		clock_gettime(CLOCK_MONOTONIC, &start);
	}
	total = 0;
	idx = 0;
	ret = snprintf(dest, 50, "/sybil/fs%d/%d.pub", arg->tid, arg->tid);
	txt = open(dest, O_RDWR);
	fstat(txt, &sb);
	size = (int)sb.st_size;
	ret = read(txt,arg->buf, size);
	if (arg->tid == 0) {
		clock_gettime(CLOCK_MONOTONIC, &end);
		delta = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/BILLION;
		printf("[%d]: takes %f seconds for actual to finish.\n", fs_cnt, delta);
	}
	printf("[%d]:r %d bytes from %s.\n", arg->tid, ret, dest);
}

int main(int argc, char *argv[]) {
	int i, ret;
	pthread_t tid, actual;
	char *data;
	if (argc == 2) {
		fs_cnt = atoi(argv[1]);
		printf("traces replay on %d fses..\n", fs_cnt);
	} else {
		printf("plz supply correct arguments!\n");
		exit(0);
	}
	/* prepare the data buffer */
	data = malloc(9000);
	memset(data, 'a', 9000);
	/* prepare the file with some data first */
	for (i = 0; i < fs_cnt; i++) {
		int j;
		char key_file[128];
		for (j = 0; j < 20; j++) {
			int ret;
			ret = snprintf(key_file, 50, "/sybil/fs%d/%d.pub", i, j);
			ret = open(key_file, O_RDWR);
			write(ret, data, (random() % 512) + 512);
			fsync(ret);
			close(ret);
		}
	}
	printf("done creating pub key files...\n");
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
