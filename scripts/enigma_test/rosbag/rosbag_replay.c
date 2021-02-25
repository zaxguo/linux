#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>


#define SYBIL_CNT 10

struct args {
	int tid;
	char *data;
};

int *rosbag_lib;

static int get_write_from_trace(void) {
	return 0;
}

static void *test_write(void *args) {
	int ret, write_size, total, txt;
	char dest[50];
	struct args *arg = (struct args*) args;
	double start, end, delta;
	if (arg->tid == 0) {
		start = clock();
	}
	total = 0;
	ret = snprintf(dest, 50, "/sybil/fs%d/test.txt", arg->tid);
	txt = open(dest, O_RDWR);
	do {
		write_size = get_write_from_trace();
		ret = write(txt, arg->data, write_size);
		if (ret > 0) {
			total += ret;
		}
	} while(ret == write_size);
	fsync(txt);
	if (arg->tid == 1) {
		end = clock();
		delta = (end - start)/CLOCKS_PER_SEC;
		printf("takes %f seconds for actual to finish.\n", delta);
	}
	printf("has written %d bytes to %s.\n", total, dest);
}

static int* construct_lib(char *lib_path) {
	FILE *lib;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int lib_idx = 0;
	lib = fopen(lib_path, "r");
	rosbag_lib = malloc(8000 * sizeof(int));
	if (lib == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	while ((nread = getline(&line, &len, lib)) != -1) {
		int cnt, idx, res;
		cnt = 0; idx = 0;
		while (cnt < 2 && idx < strlen(line)) {
			if (line[idx++] == ',')
				cnt++;
		}
		res = atoi(line + idx);
		rosbag_lib[lib_idx++] = res;
		printf("%d\n", res);
	}
	free(line);
	fclose(lib);
}


int main() {
	int i, ret;
	pthread_t tid, actual;
	char *data;

	construct_lib("../rosbag_logs/output/test.log");
	return 0;
	/* large write */
	data = malloc(80000);
	memset(data, 'a', 80000);
	for (i = 1; i < SYBIL_CNT; i++) {
		struct args* arg = malloc(sizeof(struct args));
		arg->tid = i;
		arg->data = data;
		ret = pthread_create(&tid, NULL, test_write, (void *)arg);
		if (i == 0) {
			actual = tid;
		}
	}
	/* wait for the actual to finish */
	pthread_join(tid, NULL);
	/*pthread_join(actual, NULL);*/
	pthread_exit(0);
	return 0;
}
