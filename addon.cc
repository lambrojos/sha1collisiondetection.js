#include <nan.h>
#include "lib/myobject.h"

using namespace v8;

void CreateObject(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  info.GetReturnValue().Set(MyObject::NewInstance(info[0]));
}

void Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj1 = Nan::ObjectWrap::Unwrap<MyObject>(info[0]->ToObject());
  MyObject* obj2 = Nan::ObjectWrap::Unwrap<MyObject>(info[1]->ToObject());
  double sum = obj1->Val() + obj2->Val();
  info.GetReturnValue().Set(Nan::New(sum));
}

void Check(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	SHA1_CTX ctx2;
	SHA1DCInit(&ctx2);
  info.GetReturnValue().Set(Nan::New(1));
}

void InitAll(v8::Local<v8::Object> exports) {
  MyObject::Init();

  exports->Set(Nan::New("createObject").ToLocalChecked(),
      Nan::New<v8::FunctionTemplate>(CreateObject)->GetFunction());

  exports->Set(Nan::New("check").ToLocalChecked(),
      Nan::New<v8::FunctionTemplate>(Check)->GetFunction());

  exports->Set(Nan::New("add").ToLocalChecked(),
      Nan::New<v8::FunctionTemplate>(Add)->GetFunction());
}

NODE_MODULE(addon, InitAll)
