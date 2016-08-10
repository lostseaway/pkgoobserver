#ifndef LATLNG_HPP
#define LATLNG_HPP

#include "s2latlng.h"
#include <node.h>
#include <node_object_wrap.h>

namespace s2geo {
using namespace v8;
class LatLng : public node::ObjectWrap {
 public:
    LatLng();
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> exports);
    inline S2LatLng get() { return this_; }
    static Local<Object> CreateNew(const v8::FunctionCallbackInfo<v8::Value>& args,S2LatLng ll);

 private:
  ~LatLng();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  //method
  static void IsValid(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Normalized(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void ToPoint(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void ToString(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Distance(const v8::FunctionCallbackInfo<v8::Value>& args);
  //getter method
  static void Lat(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& args);
  static void Lng(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& args);

  S2LatLng this_;
};
}
#endif

