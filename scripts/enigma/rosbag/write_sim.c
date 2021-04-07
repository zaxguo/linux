#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>


struct args {
	int tid;
	char *data;
};

static void *test_write(void *args) {
	int ret, txt;
	char dest[50];
	struct args *arg = (struct args*) args;
	double start, end, delta;
	if (arg->tid == 0) {
		start = clock();
	}
	ret = snprintf(dest, 50, "/sybil/fs%d/test.txt", arg->tid);
	txt = open(dest, O_RDWR);
	ret = write(txt, arg->data, 80000);
	fsync(txt);
	if (arg->tid == 1) {
		end = clock();
		delta = (end - start)/CLOCKS_PER_SEC;
		printf("takes %f seconds for actual to finish.\n", delta);
	}
	printf("has written %d bytes to %s.\n", ret, dest);
}

int main() {
	int i, ret;
	pthread_t tid, actual;
	char *data;
	/* large write */
	data = malloc(80000);
	memset(data, 'a', 80000);
	for (i = 1; i < 2; i++) {
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
