#ifndef POINT_HPP
#define POINT_HPP

#include <node.h>
#include <node_object_wrap.h>
#include "s2.h"

namespace s2geo {
class Point : public node::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);
    inline S2Point get() { return this_; }
    static v8::Local<v8::Object> CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args,S2Point c);
    static v8::Persistent<v8::FunctionTemplate> constructor;

protected:
    Point();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void X(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Y(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Z(const v8::FunctionCallbackInfo<v8::Value>& args);


    S2Point this_;
};
}
#endif
