#include "cap.h"

namespace s2geo {
using namespace v8;

Persistent<FunctionTemplate> Cap::constructor;

void Cap::Init(Local<Object> exports) {
   Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "S2Cap"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(tpl, "getRectBound", GetRectBound);
    NODE_SET_PROTOTYPE_METHOD(tpl, "intersects", Intersects);
    NODE_SET_PROTOTYPE_METHOD(tpl, "interiorIntersects", InteriorIntersects);
    NODE_SET_PROTOTYPE_METHOD(tpl, "contains", Contains);
    NODE_SET_PROTOTYPE_METHOD(tpl, "complement", Complement);

    constructor.Reset(isolate, tpl);
    exports->Set(String::NewFromUtf8(isolate, "S2Cap"),
               tpl->GetFunction());
}

Cap::Cap()
    : ObjectWrap(),
      this_() {}

void Cap::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (!args.IsConstructCall()) {
         isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
                    return;
    }


    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Cap* ll = static_cast<Cap*>(ptr);
        ll->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        return;
    }

    Cap* obj = new Cap();

    obj->Wrap(args.This());

    if (args.Length() == 2 && args[1]->IsNumber()) {
        Local<Object> fromObj = args[0]->ToObject();
        Local<FunctionTemplate> point = Local<FunctionTemplate>::New(isolate,Point::constructor);
        if (point->HasInstance(fromObj)) {
            S2Point p = node::ObjectWrap::Unwrap<Point>(fromObj)->get();
            obj->this_ = S2Cap::FromAxisHeight(p, args[1]->ToNumber()->Value());
        } else {
            isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "S2Cap requires arguments (S2Point, number)")));
                    return;
        }
    } else {
        isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate,"S2Cap requires arguments (S2Point, number)")));
                    return;
    }

    args.GetReturnValue().Set(args.This());
}

Local<Object> Cap::CreateNew(const FunctionCallbackInfo<Value>& args,S2Cap s2cap) {
    Isolate* isolate = args.GetIsolate();
    Cap* obj = new Cap();
    obj->this_ = s2cap;
    Local<Value> ext = External::New(isolate,obj);
    Local<FunctionTemplate> cons = Local<FunctionTemplate>::New(isolate,constructor);
    Local<Context> context=  isolate->GetCurrentContext();
    Local<Object> handleObject = cons->GetFunction()->NewInstance(context, 1, &ext).ToLocalChecked();
    return handleObject;
}

void Cap::GetRectBound(const FunctionCallbackInfo<Value>& args){
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.Holder());
    args.GetReturnValue().Set(LatLngRect::CreateNew(args,cap->this_.GetRectBound()));
}

void Cap::Intersects(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.Holder());
    S2Cap other = node::ObjectWrap::Unwrap<Cap>(args[0]->ToObject())->get();
    args.GetReturnValue().Set(Boolean::New(isolate,cap->this_.Intersects(other)));
}

void Cap::InteriorIntersects(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.Holder());
    S2Cap other = node::ObjectWrap::Unwrap<Cap>(args[0]->ToObject())->get();
    args.GetReturnValue().Set(Boolean::New(isolate,cap->this_.Intersects(other)));
}

void Cap::Contains(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.Holder());
    S2Cap other = node::ObjectWrap::Unwrap<Cap>(args[0]->ToObject())->get();
    args.GetReturnValue().Set(Boolean::New(isolate,cap->this_.Contains(other)));
}

void Cap::Complement(const FunctionCallbackInfo<Value>& args){
    Cap* cap = node::ObjectWrap::Unwrap<Cap>(args.Holder());
    args.GetReturnValue().Set(Cap::CreateNew(args,cap->this_.Complement()));
}
}
