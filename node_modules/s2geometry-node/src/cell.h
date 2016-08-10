#ifndef CELL_HPP
#define CELL_HPP

#include <node.h>
#include "s2cell.h"
#include "s2cellid.h"
#include "s2.h"
#include "s2latlng.h"
#include "latlng.h"
#include "point.h"
#include "cap.h"
#include "cellid.h"
namespace s2geo{
class Cell : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> target);
    inline S2Cell get() { return this_; }
    static Local<Object> CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args,S2Cell c);
    static Local<Object> CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args,S2CellId c);

protected:
    Cell();

    static void  New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  ApproxArea(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  ExactArea(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  Face(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  Level(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  AverageArea(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  Orientation(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  IsLeaf(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  GetCapBound(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  GetCenter(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  GetVertex(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  ToString(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void  Id(const v8::FunctionCallbackInfo<v8::Value>& args);

    S2Cell this_;
};
}
#endif
