#ifndef INC_LOG_H
#define INC_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mqueue.h>

#define ERROR_VAL 0
#define SUCCESS_VAL 1
#define MQ_NAME "/mq-comlog"
#define MAX_MSG_SIZE 512
#define MAX_TAGS 30
#define MAX_TAG_VALUE 65000

/* queue descriptor */
mqd_t mqdes;

int client_init();
int client_log(uint16_t *tag_buf, int num_tags, char *mesg);

#endif  /* _INC_LOG_H */
