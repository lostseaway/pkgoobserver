#include "point.h"

using namespace v8;

namespace s2geo{
Persistent<FunctionTemplate> Point::constructor;

void Point::Init(Handle<Object> exports) {
      Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
      Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
      tpl->SetClassName(String::NewFromUtf8(isolate, "S2Point"));
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      // Prototype
      NODE_SET_PROTOTYPE_METHOD(tpl, "x", X);
      NODE_SET_PROTOTYPE_METHOD(tpl, "y", Y);
      NODE_SET_PROTOTYPE_METHOD(tpl, "z", Z);

      constructor.Reset(isolate, tpl);
      exports->Set(String::NewFromUtf8(isolate, "S2Point"),
                   tpl->GetFunction());
}

Point::Point()
    : ObjectWrap(),
      this_() {}

void Point::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

    if (!args.IsConstructCall()) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
            return;
    }

   if (args[0]->IsExternal()) {
           Local<External> ext = Local<External>::Cast(args[0]);
           void* ptr = ext->Value();
           Point* p = static_cast<Point*>(ptr);
           p->Wrap(args.This());
           args.GetReturnValue().Set(args.This());
           return;
    }

        if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "(number, number, number) required")));
                    return;
        }

        Point* obj = new Point();

        obj->Wrap(args.This());

        obj->this_ = S2Point(
            args[0]->ToNumber()->Value(),
            args[1]->ToNumber()->Value(),
            args[2]->ToNumber()->Value());

        args.GetReturnValue().Set(args.This());
}

Local<Object> Point::CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args, S2Point point) {
        Isolate* isolate = args.GetIsolate();
        v8::TryCatch try_catch(isolate);
       Point* obj = new Point();
        obj->this_ = point;
        Local<Value> ext = External::New(isolate,obj);
        Local<Context> context = isolate->GetCurrentContext();
        Local<FunctionTemplate> cons = Local<FunctionTemplate>::New(isolate, constructor);
        
        MaybeLocal<Object> handleObject = cons->GetFunction()->NewInstance(context,1, &ext);
        v8::String::Utf8Value exception(try_catch.Exception());
        v8::String::Utf8Value stack_trace(try_catch.StackTrace());
        if(handleObject.IsEmpty()){
        if (stack_trace.length() > 0) {
            const char* stack_trace_string = *stack_trace;
            printf("%s\n", stack_trace_string);
        }
        if(exception.length() > 0){
             const char* stack_trace_string = *exception;
            printf("%s\n", stack_trace_string);
        }
        }
        return handleObject.ToLocalChecked();
}

void Point::X(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Point* obj = ObjectWrap::Unwrap<Point>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate, obj->this_.x()));
}

void Point::Y(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Point* obj = ObjectWrap::Unwrap<Point>(args.Holder());

    args.GetReturnValue().Set(Number::New(isolate, obj->this_.y()));
}

void Point::Z(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

 Point* obj = ObjectWrap::Unwrap<Point>(args.Holder());

   args.GetReturnValue().Set(Number::New(isolate, obj->this_.z()));
}
}