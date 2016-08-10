#include "latlng.h"
#include "point.h"

namespace s2geo {
using namespace v8;

Persistent<FunctionTemplate> LatLng::constructor;

void LatLng::Init(Local<Object> exports) {
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
      Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
      tpl->SetClassName(String::NewFromUtf8(isolate, "S2LatLng"));
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      // Prototype
      NODE_SET_PROTOTYPE_METHOD(tpl, "normalized", Normalized);
      NODE_SET_PROTOTYPE_METHOD(tpl, "isValid", IsValid);
      NODE_SET_PROTOTYPE_METHOD(tpl, "toPoint", ToPoint);
      NODE_SET_PROTOTYPE_METHOD(tpl, "distance", Distance);
      NODE_SET_PROTOTYPE_METHOD(tpl, "toString", ToString);

      Local<ObjectTemplate> proto = tpl->PrototypeTemplate();
      proto->SetAccessor(String::NewFromUtf8(isolate, "lat"), Lat);
      proto->SetAccessor(String::NewFromUtf8(isolate, "lng"), Lng);

      constructor.Reset(isolate, tpl);
      exports->Set(String::NewFromUtf8(isolate, "S2LatLng"),
                   tpl->GetFunction());
}

LatLng::LatLng()
    : ObjectWrap(),
      this_() {}
LatLng::~LatLng() {
}

void LatLng::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

    if (!args.IsConstructCall()) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
            return;
    }

if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        LatLng* ll = static_cast<LatLng*>(ptr);
        ll->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        return;
    }

    LatLng* obj = new LatLng();
    obj->Wrap(args.This());

    if (args.Length() == 2) {
        if (args[0]->IsNumber() &&
            args[1]->IsNumber()) {
            obj->this_ = S2LatLng::FromDegrees(
                args[0]->ToNumber()->Value(),
                args[1]->ToNumber()->Value());
        }
    } else if (args.Length() == 1) {
        Local<Object> fromObj = args[0]->ToObject();
        Local<FunctionTemplate> point = Local<FunctionTemplate>::New(isolate, Point::constructor);
        if (point->HasInstance(fromObj)) {
            S2Point p = node::ObjectWrap::Unwrap<Point>(fromObj)->get();
            obj->this_ = S2LatLng(p);
        } else {
             isolate->ThrowException(Exception::TypeError(
                            String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
                        return;
        }
    }

    args.GetReturnValue().Set(args.This());
}

Local<Object> LatLng::CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args, S2LatLng ll) {
        Isolate* isolate = args.GetIsolate();
        v8::TryCatch try_catch(isolate);
       LatLng* obj = new LatLng();
        obj->this_ = ll;
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

void LatLng::Lat(v8::Local<v8::String> property, const PropertyCallbackInfo<v8::Value>& args){
    Isolate* isolate = args.GetIsolate();
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.lat().degrees()));

}

void LatLng::Lng(v8::Local<v8::String> property, const PropertyCallbackInfo<v8::Value>& args){
    Isolate* isolate = args.GetIsolate();
    LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.lng().degrees()));

}

void LatLng::IsValid(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.Holder());

  args.GetReturnValue().Set(Boolean::New(isolate, obj->this_.is_valid()));
}

void LatLng::Normalized(const FunctionCallbackInfo<Value>& args) {
  LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.Holder());
  args.GetReturnValue().Set(LatLng::CreateNew(args,obj->this_.Normalized()));
}

void LatLng::ToPoint(const FunctionCallbackInfo<Value>& args) {
   LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.Holder());
   args.GetReturnValue().Set(Point::CreateNew(args,obj->this_.ToPoint()));
}

void LatLng::Distance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  LatLng* latlng = node::ObjectWrap::Unwrap<LatLng>(args.Holder());
  S2LatLng other = node::ObjectWrap::Unwrap<LatLng>(args[0]->ToObject())->get();

  args.GetReturnValue().Set(Number::New(isolate,latlng->this_.GetDistance(other).degrees()));
}

void LatLng::ToString(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  LatLng* obj = ObjectWrap::Unwrap<LatLng>(args.Holder());

  args.GetReturnValue().Set(String::NewFromUtf8(isolate,obj->this_.ToStringInDegrees().c_str()));
}
}
