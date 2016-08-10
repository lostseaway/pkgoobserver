#include "cellid.h"


namespace s2geo {

using namespace v8;

Persistent<FunctionTemplate> CellId::constructor;

CellId::CellId()
    : ObjectWrap(),
      this_() {}

CellId::~CellId() {
}

void CellId::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "S2CellID"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype

    NODE_SET_PROTOTYPE_METHOD(tpl, "level", Level);
    NODE_SET_PROTOTYPE_METHOD(tpl, "toToken", ToToken);
    NODE_SET_PROTOTYPE_METHOD(tpl, "fromToken", FromToken);
    NODE_SET_PROTOTYPE_METHOD(tpl, "toPoint", ToPoint);
    NODE_SET_PROTOTYPE_METHOD(tpl, "toString", ToString);
    NODE_SET_PROTOTYPE_METHOD(tpl, "toLatLng", ToLatLng);
    NODE_SET_PROTOTYPE_METHOD(tpl, "parent", Parent);
    NODE_SET_PROTOTYPE_METHOD(tpl, "prev", Prev);
    NODE_SET_PROTOTYPE_METHOD(tpl, "next", Next);
    NODE_SET_PROTOTYPE_METHOD(tpl, "child_begin", ChildBegin);
    NODE_SET_PROTOTYPE_METHOD(tpl, "child_end", ChildEnd);
    NODE_SET_PROTOTYPE_METHOD(tpl, "isFace", IsFace);
    NODE_SET_PROTOTYPE_METHOD(tpl, "rangeMin", RangeMin);
    NODE_SET_PROTOTYPE_METHOD(tpl, "rangeMax", RangeMax);
    NODE_SET_PROTOTYPE_METHOD(tpl, "id", Id);
    NODE_SET_PROTOTYPE_METHOD(tpl, "idString", IdString);
    NODE_SET_PROTOTYPE_METHOD(tpl, "child", Child);
    NODE_SET_PROTOTYPE_METHOD(tpl, "children", Children);
    NODE_SET_PROTOTYPE_METHOD(tpl, "contains", Contains);

  constructor.Reset(isolate, tpl);
  exports->Set(String::NewFromUtf8(isolate, "S2CellId"),
               tpl->GetFunction());
}

void CellId::New(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (!args.IsConstructCall()) {
        isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
                    return;
    }
    
    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        CellId* cellid = static_cast<CellId*>(ptr);
        cellid->Wrap(args.This());
         args.GetReturnValue().Set(args.This());
        return;
    }

    CellId* obj = new CellId();

    obj->Wrap(args.This());

    if (args.Length() == 1) {
        Local<Object> fromObj = args[0]->ToObject();
        Local<FunctionTemplate> point = Local<FunctionTemplate>::New(isolate, Point::constructor);
        Local<FunctionTemplate> latlng = Local<FunctionTemplate>::New(isolate, LatLng::constructor);
        if (point->HasInstance(fromObj)) {
            S2Point p = node::ObjectWrap::Unwrap<Point>(fromObj)->get();
            obj->this_ = S2CellId::FromPoint(p);
        } else if (latlng->HasInstance(fromObj)) {
            S2LatLng ll = node::ObjectWrap::Unwrap<LatLng>(fromObj)->get();
            obj->this_ = S2CellId::FromLatLng(ll);
        } else if (args[0]->IsString()) {
            v8::String::Utf8Value str(args[0]->ToString());
            std::string strnum {*str};
            obj->this_ = S2CellId(ParseLeadingUInt64Value(strnum, 0));
        } else {
            isolate->ThrowException(Exception::TypeError(
                                    String::NewFromUtf8(isolate, "Invalid input.")));
                                return;
        }
    } else {
        obj->this_ = S2CellId();
    }

     args.GetReturnValue().Set(args.This());
}

Local<Object> CellId::CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args, S2CellId s2cellid) {
        Isolate* isolate = args.GetIsolate();
        v8::TryCatch try_catch(isolate);
        CellId* obj = new CellId();
        obj->this_ = s2cellid;
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

void CellId::FromToken(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (args.Length() != 1 || !args[0]->IsString()) {
            isolate->ThrowException(Exception::TypeError(
                                                    String::NewFromUtf8(isolate,("(str) required"))));
            return;
        }
         v8::String::Utf8Value str(args[0]->ToString());
        std::string strtoken {*str};
        CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
        obj->this_ = S2CellId::FromToken(strtoken);
     args.GetReturnValue().Set(args.This());
}

void CellId::Level(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.level()));
}

void CellId::ToToken(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(String::NewFromUtf8(isolate,obj->this_.ToToken().c_str()));
}

void CellId::ToString(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(String::NewFromUtf8(isolate,obj->this_.ToString().c_str()));
}

void CellId::ToPoint(const FunctionCallbackInfo<Value>& args) {

    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(Point::CreateNew(args,obj->this_.ToPoint()));
}

void CellId::Parent(const FunctionCallbackInfo<Value>& args) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    if (args.Length() == 1 && args[0]->IsNumber()) {
             args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.parent(args[0]->ToNumber()->Value())));
     } else {
            args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.parent()));
     }
}

void CellId::Prev(const FunctionCallbackInfo<Value>& args) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.prev()));
}

void CellId::Next(const FunctionCallbackInfo<Value>& args) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.next()));
}

void CellId::ChildBegin(const FunctionCallbackInfo<Value>& args) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.child_begin()));
}

void CellId::ChildEnd(const FunctionCallbackInfo<Value>& args) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.child_end()));
}


void CellId::IsFace(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(Boolean::New(isolate,obj->this_.is_face()));
}

void CellId::RangeMin(const FunctionCallbackInfo<Value>& args) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.range_min()));
}

void CellId::RangeMax(const FunctionCallbackInfo<Value>& args) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.range_max()));
}

void CellId::Contains(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    CellId* cellid = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    S2CellId other = node::ObjectWrap::Unwrap<CellId>(args[0]->ToObject())->get();
    args.GetReturnValue().Set(Boolean::New(isolate,cellid->this_.contains(other)));
}

void CellId::Children(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    S2CellId cell_id = obj->this_.child_begin();
    S2CellId end = obj->this_.child_end();
    Local<Set> nodes = Set::New(isolate);

    while(cell_id != end){
        char str[21];
        sprintf(str, "%llu", cell_id.id());
        Local<String> strValue = String::NewFromUtf8(isolate,str);
        nodes->Add(isolate->GetCurrentContext(),strValue);
        cell_id = cell_id.next();
    }
    args.GetReturnValue().Set(nodes->AsArray());
}

void CellId::Id(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    char str[21];
    sprintf(str, "%llu", obj->this_.id());
    args.GetReturnValue().Set(String::NewFromUtf8(isolate,str));
}

void CellId::IdString(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, std::to_string(obj->this_.id()).c_str()));
}

void CellId::Child(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
        if (args.Length() != 1) {
            isolate->ThrowException(Exception::TypeError(
                                        String::NewFromUtf8(isolate,("(number) required"))));
            return;
        }
    args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.child(args[0]->ToNumber()->Value())));
}


void CellId::ToLatLng(const FunctionCallbackInfo<Value>& args) {
    CellId* obj = node::ObjectWrap::Unwrap<CellId>(args.Holder());
    args.GetReturnValue().Set(LatLng::CreateNew(args,obj->this_.ToLatLng()));
}
}
