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
};

int *rosbag_lib;
int fs_cnt = DEFAULT_FS_CNT;

static int replay_write_from_trace(int idx) {
	return rosbag_lib[idx];
}

static void *test_write(void *args) {
	int ret, write_size, total, txt, idx;
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
		write_size = replay_write_from_trace(idx++);
		/*printf("[%d]:idx = %d, write_size = %d\n", arg->tid, idx, write_size);*/
		ret = write(txt, arg->data, write_size);
		if (ret > 0) {
			total += ret;
		}
		/*printf("[%d]:ret = %d, write_size = %d\n", arg->tid, ret, write_size);*/
	} while(ret == write_size);
	fsync(txt);
	if (arg->tid == 0) {
		clock_gettime(CLOCK_MONOTONIC, &end);
		delta = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/BILLION;
		printf("[%d]: takes %f seconds for actual to finish.\n", fs_cnt, delta);
	}
	printf("[%d] has written %d bytes to %s.\n", arg->tid, total, dest);
}

static int* construct_lib(char *lib_path) {
	FILE *lib;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int lib_idx = 0;
	lib = fopen(lib_path, "r");
	rosbag_lib = malloc(MAX_RECORDS * sizeof(int));
	if (lib == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	while (((nread = getline(&line, &len, lib)) != -1) && lib_idx < MAX_RECORDS) {
		int cnt, idx, res;
		cnt = 0; idx = 0;
		while (cnt < 2 && idx < strlen(line)) {
			if (line[idx++] == ',')
				cnt++;
		}
		res = atoi(line + idx);
		rosbag_lib[lib_idx++] = res;
	}
	free(line);
	fclose(lib);
	return rosbag_lib;
}


int main(int argc, char *argv[]) {
	int i, ret;
	pthread_t tid, actual;
	char *data;
	int *trace_lib;
	trace_lib = construct_lib("../rosbag_logs/output/test.log");
	/* prepare the data */
	data = malloc(900000);
	memset(data, 'a', 900000);
	if (argc == 2) {
		fs_cnt = atoi(argv[1]);
	}
	printf("rosbag traces replay on %d fses..\n", fs_cnt);
	for (i = 0; i < fs_cnt; i++) {
		struct args* arg = malloc(sizeof(struct args));
		arg->tid = i;
		arg->data = data;
		ret = pthread_create(&tid, NULL, test_write, (void *)arg);
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
