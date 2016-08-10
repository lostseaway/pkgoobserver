#ifndef NODES2INTERVAL_HPP
#define NODES2INTERVAL_HPP

#include <node.h>
#include "node_object_wrap.h"   
#include "s1interval.h"
#include "s2.h"
#include "s1angle.h"
#include "latlng.h"
#include "point.h"

namespace s2geo{
using namespace v8;
class Interval : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Handle<v8::Object> target);
    inline S1Interval get() { return this_; }
    static v8::Local<v8::Object> CreateNew(const FunctionCallbackInfo<Value>& args, S1Interval c);

protected:
    Interval();

    static void New(const FunctionCallbackInfo<Value>& args);
    static void GetLength(const FunctionCallbackInfo<Value>& args);
    static void GetCenter(const FunctionCallbackInfo<Value>& args);
    static void GetComplementCenter(const FunctionCallbackInfo<Value>& args);
    static void GetHi(const FunctionCallbackInfo<Value>& args);
    static void GetLo(const FunctionCallbackInfo<Value>& args);
    static void Contains(const FunctionCallbackInfo<Value>& args);

    S1Interval this_;
};
}
#endif
