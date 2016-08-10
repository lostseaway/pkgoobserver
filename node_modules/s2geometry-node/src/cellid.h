// myobject.h
#ifndef CELLID_H
#define CELLID_H

#include <node.h>
#include <node_object_wrap.h>
#include "s2.h"
#include "s2cell.h"
#include "s2cellid.h"
#include "s2latlng.h"
#include "latlng.h"
#include "point.h"
#include "strutil.h"
using namespace v8;
namespace s2geo{
class CellId : public node::ObjectWrap {

public:
    CellId();
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> exports);
    static Local<Object> CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args, S2CellId c);
    inline S2CellId get() { return this_; }

protected:
    ~CellId();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Level(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ToToken(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ToPoint(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ToLatLng(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ToString(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void FromToken(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Parent(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Prev(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Next(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ChildBegin(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ChildEnd(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Children(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void IsFace(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void RangeMin(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void RangeMax(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Id(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void IdString(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Child(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Contains(const v8::FunctionCallbackInfo<v8::Value>& args);

    S2CellId this_;
};
}
#endif

