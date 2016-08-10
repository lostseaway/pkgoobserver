#include <node.h>
#include "point.h"
#include "latlng.h"
#include "cellid.h"
#include "cell.h"
#include "latlngrect.h"
#include "cap.h"
#include "interval.h"
#include "angle.h"


using namespace v8;
namespace s2geo{
void InitAll(Local<Object> exports) {
    Point::Init(exports);
    LatLng::Init(exports);
    CellId::Init(exports);
    Cap::Init(exports);
    LatLngRect::Init(exports);
    Cell::Init(exports);
    Interval::Init(exports);
    Angle::Init(exports);
}

NODE_MODULE(NativeExtension, InitAll)
}