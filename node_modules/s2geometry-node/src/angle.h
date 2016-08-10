#ifndef NODES2ANGLE_HPP
#define NODES2ANGLE_HPP

#include <node.h>
#include "node_object_wrap.h" 
#include "s2.h"
#include "s1angle.h"
#include "latlng.h"
#include "point.h"

namespace s2geo{
using namespace v8;
class Angle : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> exports);
    inline S1Angle get() { return this_; }
    static v8::Local<v8::Object> CreateNew(const FunctionCallbackInfo<Value>& args, S1Angle c);

protected:
    Angle();

    static void New(const FunctionCallbackInfo<Value>& args);
    static void Normalize(const FunctionCallbackInfo<Value>& args);

    S1Angle this_;
};
}
#endif
