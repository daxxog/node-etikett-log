#include "log.h"

int
client_init()
{
	mqdes = mq_open(MQ_NAME, O_WRONLY);
	if (mqdes < 0) {
		perror("mq_open");
		return (int) ERROR_VAL;
	}

	return (int) SUCCESS_VAL;
}

int
client_log(uint16_t *tag_buf, int num_tags, char *mesg)
{
	int msg_len = strlen(mesg) + 1;
	if (msg_len + num_tags * sizeof(uint16_t) > MAX_MSG_SIZE) {
		return (int) ERROR_VAL;
	}

	if (memcpy((char *) (tag_buf + num_tags + 1), mesg, msg_len) < 1) {
		perror("memcpy");
		return (int) ERROR_VAL;
	}

	if (mq_send(mqdes, (char *) tag_buf, (num_tags + 1) * sizeof(uint16_t) + msg_len, 1) < 0) {
		perror("mq_send");
		return (int) ERROR_VAL;
	}	
	printf("num_tag: %hu\n", *tag_buf);
	printf("mesg: %s\n", (char *) (tag_buf + num_tags + 1));


	return (int) SUCCESS_VAL;
}
