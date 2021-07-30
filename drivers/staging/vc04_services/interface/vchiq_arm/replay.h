#ifndef __REPALY_H_
#define __REPLAY_H_

/* annotated offsets of the data fields */
/* buffer to host containing frame size */
int buffer_to_host_98 = 0x6438;
/* bulk_rx containing pagelist */
int off_100 = 0x24ca0;

static inline int check_msg_header(int *head, int type) {
	return (*head == 0x6c616d6d) && (*(head + 1) == type);
}


#endif
