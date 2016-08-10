#include "latlngrect.h"

namespace s2geo {
using namespace v8;

Persistent<FunctionTemplate> LatLngRect::constructor;

void LatLngRect::Init(Handle<Object> exports) {
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
      Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
      tpl->SetClassName(String::NewFromUtf8(isolate, "S2LatLngRect"));
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      // Prototype
      NODE_SET_PROTOTYPE_METHOD(tpl, "center", GetCenter);
      NODE_SET_PROTOTYPE_METHOD(tpl, "size", GetSize);
      NODE_SET_PROTOTYPE_METHOD(tpl, "area", GetArea);
      NODE_SET_PROTOTYPE_METHOD(tpl, "getVertex", GetVertex);
      NODE_SET_PROTOTYPE_METHOD(tpl, "getCapBound", GetCapBound);
      NODE_SET_PROTOTYPE_METHOD(tpl, "contains", Contains);
      NODE_SET_PROTOTYPE_METHOD(tpl, "isValid", IsValid);
      NODE_SET_PROTOTYPE_METHOD(tpl, "isEmpty", IsEmpty);
      NODE_SET_PROTOTYPE_METHOD(tpl, "isPoint", IsPoint);
      NODE_SET_PROTOTYPE_METHOD(tpl, "union", Union);
      NODE_SET_PROTOTYPE_METHOD(tpl, "intersection", Intersection);
      NODE_SET_PROTOTYPE_METHOD(tpl, "approxEquals", ApproxEquals);

      constructor.Reset(isolate, tpl);
      exports->Set(String::NewFromUtf8(isolate, "S2LatLngRect"),
                   tpl->GetFunction());
}

LatLngRect::LatLngRect()
    : ObjectWrap(),
      this_() {}

void LatLngRect::New(const FunctionCallbackInfo<Value>& args) {
   Isolate* isolate = args.GetIsolate();

    if (!args.IsConstructCall()) {
         isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
                return;
    }

    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        LatLngRect* ll = static_cast<LatLngRect*>(ptr);
        ll->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        return;
    }

    if (args.Length() == 0) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate,"(latlng) or (latlng, latlng) required")));
                return;
    }

    LatLngRect* obj = new LatLngRect();

    obj->Wrap(args.This());


    Local<Object> ll = args[0]->ToObject();
    Local<FunctionTemplate> latlng = Local<FunctionTemplate>::New(isolate,LatLng::constructor);
    if (latlng->HasInstance(ll)) {
           isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate,"(latlng) required")));
                return;
    }

    if (args.Length() == 1) {
        obj->this_ = S2LatLngRect(
            S2LatLngRect::FromPoint(node::ObjectWrap::Unwrap<LatLng>(ll)->get()));
    } else if (args.Length() == 2) {
        Local<Object> llb = args[1]->ToObject();
        
        if (latlng->HasInstance(llb)) {
             isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate,"(latlng) required")));
                return;
        }

        obj->this_ = S2LatLngRect(
            S2LatLngRect::FromPointPair(
                node::ObjectWrap::Unwrap<LatLng>(ll)->get(),
                node::ObjectWrap::Unwrap<LatLng>(llb)->get()));
    }

    args.GetReturnValue().Set(args.This());
}

Local<Object> LatLngRect::CreateNew(const FunctionCallbackInfo<Value>& args,S2LatLngRect s2cell) {
    Isolate* isolate = args.GetIsolate();
    LatLngRect* obj = new LatLngRect();
    obj->this_ = s2cell;
    Local<Value> ext = External::New(isolate,obj);
    Local<FunctionTemplate> cons = Local<FunctionTemplate>::New(isolate,constructor);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> handleObject = cons->GetFunction()->NewInstance(context,1, &ext).ToLocalChecked();
    return handleObject;
}

void LatLngRect::GetCenter(const FunctionCallbackInfo<Value>& args){
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    args.GetReturnValue().Set(LatLng::CreateNew(args,latlngrect->this_.GetCenter()));
}

void LatLngRect::GetCapBound(const FunctionCallbackInfo<Value>& args){
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    args.GetReturnValue().Set(Cap::CreateNew(args,latlngrect->this_.GetCapBound()));
}

void LatLngRect::GetSize(const FunctionCallbackInfo<Value>& args) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    args.GetReturnValue().Set(LatLng::CreateNew(args,latlngrect->this_.GetSize()));
}

void LatLngRect::GetArea(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,latlngrect->this_.Area()));
}

void LatLngRect::GetVertex(const FunctionCallbackInfo<Value>& args) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    args.GetReturnValue().Set(LatLng::CreateNew(args,latlngrect->this_.GetVertex(args[0]->ToNumber()->Value())));
}

void LatLngRect::Contains(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    S2LatLng other = node::ObjectWrap::Unwrap<LatLng>(args[0]->ToObject())->get();
    args.GetReturnValue().Set(Boolean::New(isolate,latlngrect->this_.Contains(other)));
}

void LatLngRect::IsValid(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    args.GetReturnValue().Set(Boolean::New(isolate,latlngrect->this_.is_valid()));
}

void LatLngRect::IsEmpty(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    args.GetReturnValue().Set(Boolean::New(isolate,latlngrect->this_.is_empty()));
}

void LatLngRect::IsPoint(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    args.GetReturnValue().Set(Boolean::New(isolate,latlngrect->this_.is_point()));
}

void LatLngRect::Union(const FunctionCallbackInfo<Value>& args){
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    S2LatLngRect other = node::ObjectWrap::Unwrap<LatLngRect>(args[0]->ToObject())->get();
    args.GetReturnValue().Set(LatLngRect::CreateNew(args,latlngrect->this_.Union(other)));
}

void LatLngRect::Intersection(const FunctionCallbackInfo<Value>& args) {
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    S2LatLngRect other = node::ObjectWrap::Unwrap<LatLngRect>(args[0]->ToObject())->get();
    args.GetReturnValue().Set(LatLngRect::CreateNew(args,latlngrect->this_.Intersection(other)));
}

void LatLngRect::ApproxEquals(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    LatLngRect* latlngrect = node::ObjectWrap::Unwrap<LatLngRect>(args.Holder());
    S2LatLngRect other = node::ObjectWrap::Unwrap<LatLngRect>(args[0]->ToObject())->get();
    args.GetReturnValue().Set(Boolean::New(isolate,latlngrect->this_.ApproxEquals(other)));
}
}