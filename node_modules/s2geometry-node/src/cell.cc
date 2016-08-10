#include "cell.h"

namespace s2geo {
using namespace v8;

Persistent<FunctionTemplate> Cell::constructor;

void Cell::Init(Local<Object> exports) {
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "S2Cell"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(tpl, "approxArea", ApproxArea);
    NODE_SET_PROTOTYPE_METHOD(tpl, "exactArea", ExactArea);
    NODE_SET_PROTOTYPE_METHOD(tpl, "averageArea", AverageArea);
    NODE_SET_PROTOTYPE_METHOD(tpl, "face", Face);
    NODE_SET_PROTOTYPE_METHOD(tpl, "level", Level);
    NODE_SET_PROTOTYPE_METHOD(tpl, "orientation", Orientation);
    NODE_SET_PROTOTYPE_METHOD(tpl, "isLeaf", IsLeaf);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getCapBound", GetCapBound);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getVertex", GetVertex);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getCenter", GetCenter);
    NODE_SET_PROTOTYPE_METHOD(tpl, "id", Id);
    NODE_SET_PROTOTYPE_METHOD(tpl, "toString", ToString);

    constructor.Reset(isolate, tpl);
    exports->Set(String::NewFromUtf8(isolate, "S2Cell"),
               tpl->GetFunction());
}

Cell::Cell()
    : ObjectWrap(),
      this_() {}

void Cell::New(const FunctionCallbackInfo<Value>& args) {
   Isolate* isolate = args.GetIsolate();

    if (!args.IsConstructCall()) {
        isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
                    return;
    }
    
    if (args[0]->IsExternal()) {
        Local<External> ext = Local<External>::Cast(args[0]);
        void* ptr = ext->Value();
        Cell* ll = static_cast<Cell*>(ptr);
        ll->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        return;
    }

    if (args.Length() != 1) {
        isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "(lat,lng) required.")));
                    return;
    }

    Cell* obj = new Cell();

    obj->Wrap(args.This());
    Local<Object> ll = args[0]->ToObject();
    Local<FunctionTemplate> latlng = Local<FunctionTemplate>::New(isolate, LatLng::constructor);
    Local<FunctionTemplate> cellId = Local<FunctionTemplate>::New(isolate, CellId::constructor);
    if (latlng->HasInstance(ll)) {
        obj->this_ = S2Cell(
            S2CellId::FromLatLng(node::ObjectWrap::Unwrap<LatLng>(ll)->get()));
    } else if (cellId->HasInstance(ll)) {
        obj->this_ = S2Cell(node::ObjectWrap::Unwrap<CellId>(ll)->get());
    } else {
        isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "(lat,lng) or (cellid) required.")));
                    return;
    }

     args.GetReturnValue().Set(args.This());
}

Local<Object> Cell::CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args, S2Cell s2cell) {
        Isolate* isolate = args.GetIsolate();
        v8::TryCatch try_catch(isolate);
        Cell* obj = new Cell();
        obj->this_ = s2cell;
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

Local<Object> Cell::CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args, S2CellId s2cellid) {
        Isolate* isolate = args.GetIsolate();
        v8::TryCatch try_catch(isolate);
        Cell* obj = new Cell();
        obj->this_ = S2Cell(s2cellid);
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

void Cell::ApproxArea(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.ApproxArea()));
}

void Cell::ExactArea(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.ExactArea()));
}

void Cell::AverageArea(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.AverageArea(args[0]->ToNumber()->Value())));
}
void Cell::Face(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.face()));
}

void Cell::Level(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.level()));
}

void Cell::Orientation(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Number::New(isolate,obj->this_.orientation()));
}

void Cell::IsLeaf(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Boolean::New(isolate,obj->this_.is_leaf()));
}

void Cell::GetCapBound(const FunctionCallbackInfo<Value>& args) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Cap::CreateNew(args,obj->this_.GetCapBound()));
}

void Cell::GetCenter(const FunctionCallbackInfo<Value>& args) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Point::CreateNew(args,obj->this_.GetCenterRaw()));
}

void Cell::Id(const FunctionCallbackInfo<Value>& args) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(CellId::CreateNew(args,obj->this_.id()));
}

void Cell::ToString(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(String::NewFromUtf8(isolate,obj->this_.id().ToString().c_str()));
}

void Cell::GetVertex(const FunctionCallbackInfo<Value>& args) {
    Cell* obj = ObjectWrap::Unwrap<Cell>(args.Holder());
    args.GetReturnValue().Set(Point::CreateNew(args,obj->this_.GetVertex(args[0]->ToNumber()->Value())));
}
}