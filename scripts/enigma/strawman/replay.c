#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "oram.h"

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

static void replay(void *args) {
	int ret, size, total, txt, idx;
	char dest[50];
	struct args *arg = (struct args*) args;
	struct timespec start, end;
	double delta;
	clock_gettime(CLOCK_MONOTONIC, &start);
	total = 0;
	idx = 0;
	ret = snprintf(dest, 50, "./test.db");
	txt = open(dest, O_RDWR);
	do {
		struct syscall *call = get_trace_from_lib(idx++);
		if (arg->tid == 0) {
			int block_size = param->block_size;
			/* shift would be more appropriate */
			int block_id = call->offset / block_size;
			int a,b;
			a = call->size % block_size;
			b = call->size/block_size;
			int rw_cnt = (b + ((a == 0) ? (0) : (1)));
			for (int i = 0; i < rw_cnt; i++) {
				oram_access(call->op, block_id + i, arg->buf);
			}
		} else if (arg->tid == 1) {
			switch (call->op) {
				case READ:
					ret = pread(txt, arg->buf, call->size, call->offset);
					break;
				case WRITE:
					ret = pwrite(txt, arg->data, call->size, call->offset);
					break;
			}
		}
	} while(idx < lib.cnt);
	fsync(txt);
	clock_gettime(CLOCK_MONOTONIC, &end);
	delta = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/BILLION;
	printf("[%d]: takes %f seconds for %s to finish.\n", fs_cnt, delta, (arg->tid == 0) ? "oram" : "baseline");
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


int main(int argc, char *argv[]) {
	int i, ret, blocks;
	char *data, *trace_path;
	if (argc == 2) {
		trace_path = argv[1];
		printf("traces replay strawman..lib path = %s\n", trace_path);
	} else {
		printf("plz supply correct arguments!\n");
		exit(0);
	}
	ret = construct_lib(trace_path);
	blocks = create_oram_tree("dummy.bin");
	/* prepare the data buffer */
	data = malloc(9000);
	memset(data, 'a', 9000);
	struct args* arg = malloc(sizeof(struct args));
	/* read buffer */
	char *buf = malloc(9000);
	/* ORAM */
	arg->tid = 0;
	arg->data = data;
	arg->buf = buf;
	replay(arg);
	/* baseline */
	arg->tid = 1;
	replay(arg);
	return 0;
}
