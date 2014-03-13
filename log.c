#include "log.h"

int
client_init()
{
	mqdes = mq_open(MQ_NAME, O_WRONLY);
	if (mqdes < 0) {
		perror("mq_open");
		return (int)ERROR_VAL;
	}

	return (int)SUCCESS_VAL;
}

int
client_log(char *mesg)
{
	int len = strlen(mesg);
	if (len >= MAX_MSG_SIZE) {
		return (int)ERROR_VAL;
	}

	if (mq_send(mqdes, mesg, len + 1, 1) < 0) {
		perror("mq_send");
		return (int)ERROR_VAL;
	}	

	return (int)SUCCESS_VAL;
}
