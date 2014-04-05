#include <stdlib.h>
#include <node.h>
#include <v8.h>

extern "C" {
	#include "log.h"
}

using namespace v8;

uint16_t *tag_buf;
char *msg;
int i, length;

Handle<Value> log_msg(const Arguments& args) {
	HandleScope scope;
	length = args.Length();

	if (length < 1 || length > MAX_TAGS + 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Boolean::New(0));
	}
	
	if (!args[0]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Boolean::New(0));
	}

	/* store number of tags first */
	*tag_buf = (uint16_t) length - 1;
	tag_buf++;

	i = 1;
	int n = 0;
	while (i < length) {
		if (!args[i]->IsNumber() && args[i]->NumberValue() > MAX_TAG_VALUE) {
			ThrowException(Exception::TypeError(String::New("Wrong arguments")));
			return scope.Close(Boolean::New(0));
		}

		/* store tag */
		*(tag_buf + n++) = args[i++]->NumberValue();
	}

	v8::String::Utf8Value str(args[0]->ToString());
	msg = *str;
	printf("msg: %s\n", msg);

	/* log it, set tag_buf to begin at number of tags */
	if (client_log(--tag_buf, i, msg) == (int) ERROR_VAL) {
		return scope.Close(Boolean::New(0));
	}

	return scope.Close(Boolean::New(1));
}

void init(Handle<Object> exports) {
	HandleScope scope;
	exports->Set(String::NewSymbol("log"), FunctionTemplate::New(log_msg)->GetFunction());

	tag_buf = (uint16_t *) malloc(MAX_MSG_SIZE);
	if (tag_buf <= 0) {
		ThrowException(Exception::TypeError(String::New("Could not allocate memory")));
		return;
	}

	client_init();
}

NODE_MODULE(nodelog, init)
