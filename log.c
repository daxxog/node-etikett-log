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

  char *buf[MAX_MSG_SIZE];
  uint16_t *tag = (uint16_t *)buf;
  *tag = 89;
  tag = tag + 1;
  *tag = 40401;
  memcpy(tag + 1, mesg, len + 1);

	if (mq_send(mqdes, buf, 4 + len + 1, 1) < 0) {
		perror("mq_send");
		return (int)ERROR_VAL;
	}

	return (int)SUCCESS_VAL;
}
