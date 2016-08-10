#ifndef NODES2CAP_HPP
#define NODES2CAP_HPP

#include <node.h>
#include "node_object_wrap.h"
#include "s2cap.h"
#include "s2.h"
#include "s2latlngrect.h"
#include "point.h"
#include "cap.h"
#include "latlngrect.h"

namespace s2geo {
using namespace v8;
class Cap : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> exports);
    inline S2Cap get() { return this_; }
    static v8::Local<v8::Object> CreateNew(const v8::FunctionCallbackInfo<Value>& args, S2Cap ll);

protected:
    Cap();

    static void  New(const v8::FunctionCallbackInfo<Value>& args);
    static void  GetRectBound(const v8::FunctionCallbackInfo<Value>& args);
    static void  Intersects(const v8::FunctionCallbackInfo<Value>& args);
    static void  InteriorIntersects(const v8::FunctionCallbackInfo<Value>& args);
    static void  Contains(const v8::FunctionCallbackInfo<Value>& args);
    static void  Complement(const v8::FunctionCallbackInfo<Value>& args);

    S2Cap this_;
};
}
#endif
