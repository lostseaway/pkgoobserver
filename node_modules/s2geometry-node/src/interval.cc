#include "interval.h"

namespace s2geo{
using namespace v8;

Persistent<FunctionTemplate> Interval::constructor;

void Interval::Init(Local<Object> exports) {
     Isolate* isolate = exports->GetIsolate();

     // Prepare constructor template
      Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
      tpl->SetClassName(String::NewFromUtf8(isolate, "S1Interval"));
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      // Prototype
        NODE_SET_PROTOTYPE_METHOD(tpl, "length", GetLength);
        NODE_SET_PROTOTYPE_METHOD(tpl, "hi", GetHi);
        NODE_SET_PROTOTYPE_METHOD(tpl, "lo", GetLo);
        NODE_SET_PROTOTYPE_METHOD(tpl, "center", GetCenter);
        NODE_SET_PROTOTYPE_METHOD(tpl, "complementLength", GetComplementCenter);
        NODE_SET_PROTOTYPE_METHOD(tpl, "contains", Contains);

      constructor.Reset(isolate, tpl);
      exports->Set(String::NewFromUtf8(isolate, "S1Interval"),
                   tpl->GetFunction());
}

Interval::Interval()
    : ObjectWrap(),
      this_() {}

void Interval::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (!args.IsConstructCall()) {
        isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
        return;
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Interval* ll = static_cast<Interval*>(ptr);
        ll->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        return;
    }

    if (args.Length() != 1) {
       isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "(number) required.")));
        return;
    }

    Interval* obj = new Interval();

    obj->Wrap(args.This());

    obj->this_ = S1Interval::FromPoint(args[0]->ToNumber()->Value());

    args.GetReturnValue().Set(args.This());
}

Local<Object> Interval::CreateNew(const FunctionCallbackInfo<Value>& args, S1Interval s1angle) {
    Isolate* isolate = args.GetIsolate();
    Interval* obj = new Interval();
    obj->this_ = s1angle;
    Local<Value> ext = External::New(isolate,obj);
    Local<Context> context = isolate->GetCurrentContext();
    Local<FunctionTemplate> cons = Local<FunctionTemplate>::New(isolate,constructor);
    Local<Object> handleObject = cons->GetFunction()->NewInstance(context, 1, &ext).ToLocalChecked();
    return handleObject;
}

void Interval::GetLength(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.GetLength()));
}

void Interval::GetCenter(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.GetCenter()));
}

void Interval::GetComplementCenter(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.GetComplementCenter()));
}

void Interval::GetHi(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.hi()));
}

void Interval::GetLo(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.This());
    args.GetReturnValue().Set(Number::New(isolate, obj->this_.lo()));
}

void Interval::Contains(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Interval* obj = ObjectWrap::Unwrap<Interval>(args.This());
    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "(number) required.")));
    }
    if (!args[0]->IsNumber()) {
       isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "(number) required.")));
    }
    args.GetReturnValue().Set(Boolean::New(isolate,obj->this_.Contains(args[0]->ToNumber()->Value())));
}
}