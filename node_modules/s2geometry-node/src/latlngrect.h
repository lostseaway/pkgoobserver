#ifndef NODES2LATLNGRECT_HPP
#define NODES2LATLNGRECT_HPP

#include <node.h>
#include "node_object_wrap.h"
#include "s2latlngrect.h"
#include "s2cell.h"
#include "s2.h"
#include "latlng.h"
#include "cell.h"
#include "cap.h"
#include "cellid.h"
namespace s2geo{
using namespace v8;
class LatLngRect : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> exports);
    inline S2LatLngRect get() { return this_; }
    static v8::Local<v8::Object> CreateNew(const FunctionCallbackInfo<Value>& args, S2LatLngRect ll);

protected:
    LatLngRect();

    static void New(const FunctionCallbackInfo<Value>& args);
    static void  GetCenter(const FunctionCallbackInfo<Value>& args);
    static void  GetSize(const FunctionCallbackInfo<Value>& args);
    static void  GetArea(const FunctionCallbackInfo<Value>& args);
    static void  GetVertex(const FunctionCallbackInfo<Value>& args);
    static void  GetCapBound(const FunctionCallbackInfo<Value>& args);
    static void  Contains(const FunctionCallbackInfo<Value>& args);
    static void  IsValid(const FunctionCallbackInfo<Value>& args);
    static void  IsEmpty(const FunctionCallbackInfo<Value>& args);
    static void  IsPoint(const FunctionCallbackInfo<Value>& args);
    static void  Union(const FunctionCallbackInfo<Value>& args);
    static void  Intersection(const FunctionCallbackInfo<Value>& args);
    static void  ApproxEquals(const FunctionCallbackInfo<Value>& args);

    S2LatLngRect this_;
};
}
#endif
