#include "angle.h"

namespace s2geo{
using namespace v8;

Persistent<FunctionTemplate> Angle::constructor;

void Angle::Init(Handle<Object> exports) {
     Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
      Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
      tpl->SetClassName(String::NewFromUtf8(isolate, "S1Angle"));
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      // Prototype
     NODE_SET_PROTOTYPE_METHOD(tpl, "normalize", Normalize);

      constructor.Reset(isolate, tpl);
      exports->Set(String::NewFromUtf8(isolate, "S1Angle"),
                   tpl->GetFunction());
}

Angle::Angle()
    : ObjectWrap(),
      this_() {}

void Angle::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (!args.IsConstructCall()) {
         isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
                return;
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Angle* ll = static_cast<Angle*>(ptr);
        ll->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        return;
    }

    if (args.Length() != 2) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "(point,point) required.")));
                return;
    }

    Angle* obj = new Angle();

    obj->Wrap(args.This());

    Local<Object> a = args[0]->ToObject();
    Local<Object> b = args[1]->ToObject();

    Local<FunctionTemplate> point = Local<FunctionTemplate>::New(isolate,Point::constructor);
    if (!point->HasInstance(a) ||
        !point->HasInstance(b)) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "(point,point) required.")));
                return;
    }

    obj->this_ = S1Angle(
        node::ObjectWrap::Unwrap<Point>(a)->get(),
        node::ObjectWrap::Unwrap<Point>(b)->get());

   args.GetReturnValue().Set(args.This());
}

Local<Object> Angle::CreateNew(const FunctionCallbackInfo<Value>& args,S1Angle s1angle) {
    Isolate* isolate = args.GetIsolate();
    Angle* obj = new Angle();
    obj->this_ = s1angle;
    Local<Value> ext = External::New(isolate,obj);
    Local<FunctionTemplate> cons = Local<FunctionTemplate>::New(isolate,constructor);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> handleObject = cons->GetFunction()->NewInstance(context,1, &ext).ToLocalChecked();
    return handleObject;
}

void Angle::Normalize(const FunctionCallbackInfo<Value>& args) {
    Angle* obj = ObjectWrap::Unwrap<Angle>(args.This());
    obj->this_.Normalize();
    args.GetReturnValue().Set(args.This());
}
}
