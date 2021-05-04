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
#define MAX_RECORDS				11000
#define BILLION					1E9
#define FPS						10

struct args {
	int tid;
	char *data;
	char *buf;
};

int fs_cnt = DEFAULT_FS_CNT;
int *trace_lib;

static int replay_write_from_trace(int idx) {
	return trace_lib[idx];
}


static int* construct_lib(const char *lib_path) {
	FILE *lib;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int lib_idx = 0;
	lib = fopen(lib_path, "r");
	trace_lib = malloc(MAX_RECORDS * sizeof(int));
	if (lib == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	while (((nread = getline(&line, &len, lib)) != -1) && lib_idx < MAX_RECORDS) {
		int cnt, idx, res;
		cnt = 0; idx = 0;
		res = atoi(line);
		/* sleep time in terms of us */
		res = res * (1000000)/FPS;
		trace_lib[lib_idx++] = res;
	}
	free(line);
	fclose(lib);
	return trace_lib;
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
	do {
		ret = snprintf(dest, 50, "/sybil/fs%d/video%d.log", arg->tid, idx);
		txt = open(dest, O_RDWR | O_CREAT, S_IRWXU);
		ret = write(txt, arg->data, 102400);
		size = replay_write_from_trace(idx++);
		usleep(size);
		close(txt);
	} while(idx < 100);
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
	trace_lib = construct_lib("./bangor.log");
	/* prepare the data buffer */
	data = malloc(102400);
	memset(data, 'a', 102400);
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
