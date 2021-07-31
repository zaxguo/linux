#ifndef __REPALY_H_
#define __REPLAY_H_

/* annotated offsets of the data fields */
/* buffer to host containing frame size
 * get rx size via (int*)off + 21 */
#define FRAMES 2

int buffer_to_host_offs[FRAMES] = {0x5500, 0x5690};
int bulk_rx_offs[FRAMES] = {0x24198, 0x24348};
int bulk_rx_done_offs[FRAMES] = {0x5630, 0x57c0};
int curr_frame = 0;

static inline int check_msg_header(int *head, int type) {
	return (*head == 0x6c616d6d) && (*(head + 1) == type);
}

#endif
