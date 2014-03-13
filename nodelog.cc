#include <stdlib.h>
#include <node.h>
#include <v8.h>

extern "C" {
	#include "log.h"
}

using namespace v8;

Handle<Value> log_msg(const Arguments& args) {
	HandleScope scope;

	if (args.Length() < 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Boolean::New(0));
	}
	
	if (!args[0]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Boolean::New(0));
	}

	v8::String::Utf8Value str(args[0]->ToString());
	char *msg = *str;

	if (!client_log(msg)) {
		return scope.Close(Boolean::New(0));
	}

	return scope.Close(Boolean::New(1));
}

void init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("log"), FunctionTemplate::New(log_msg)->GetFunction());

	client_init();
}

NODE_MODULE(nodelog, init)
