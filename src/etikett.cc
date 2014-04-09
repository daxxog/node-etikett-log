#include <stdlib.h>
#include <node.h>
#include <v8.h>
#include <limits.h>

extern "C" {
	#include "../../libetikett/log.h"
}

using namespace v8;

uint16_t *tag_buf;
char *msg;
int i, length;

Handle<Value> log_msg(const Arguments& args) {
	HandleScope scope;
	length = args.Length();

	if (length < 1 || length > ETK_MAX_TAGS + 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Boolean::New(0));
	}
	
	if (!args[0]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Boolean::New(0));
	}

	i = 1;
	while (i < length) {
		if (!args[i]->IsNumber() && args[i]->NumberValue() > USHRT_MAX) {
			ThrowException(Exception::TypeError(String::New("Wrong arguments")));
			return scope.Close(Boolean::New(0));
		}

		*(tag_buf + i - 1) = (uint16_t) args[i++]->NumberValue();
	}

	v8::String::Utf8Value str(args[0]->ToString());
	msg = *str;

	if (etk_log(tag_buf, i - 1, msg) == (int) ETK_ERROR_VAL) {
		return scope.Close(Boolean::New(0));
	}

	return scope.Close(Boolean::New(1));
}

void init(Handle<Object> exports) {
	HandleScope scope;
	exports->Set(String::NewSymbol("log"), FunctionTemplate::New(log_msg)->GetFunction());

	tag_buf = (uint16_t *) malloc(ETK_MAX_MSG_SIZE);
	if (tag_buf == NULL) {
		ThrowException(Exception::TypeError(String::New("Could not allocate memory")));
		return;
	}

	etk_init();
}

NODE_MODULE(etikettlog, init)
