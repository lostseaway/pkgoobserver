# s2geometry-node

One day i need to play with S2 Geometry in Node, i found [node-s2](https://github.com/uber/node-s2), unfortunately that library is outdated only support node v0.10.0 so i am trying to make the  addon to be work again.

Bindings for the [S2 Geometry Library](https://code.google.com/p/s2-geometry-library/) into
[node.js](http://nodejs.org/).

For usage information, see the examples in the `examples/` directory.

## Todo List 
-. Porting More Class
-. Convert to Nan v2


## Currently Ported
* S2CellId 
* S2LatLng
* S2Point
* S2Cell
* S2Cap
* S2LatLngRect
* S1Interval
* S1Angle

## [Documentation: API.md](API.md)

## Notes

Some of the S2 API is not wrapped because it isn't meant to be exposed in this way, and is blocked from wrapping by DISALLOW_COPY_AND_ASSIGN.

* S2CellUnion
* S2Loop
* S2Polyline
* S2Polygon
* S2RegionCoverer
* S2RegionIntersection

## See Also

* [s2-geometry-javascript](https://github.com/jonatkins/s2-geometry-javascript) - an incomplete port of S2 to JavaScript.
* [gos2](https://code.google.com/p/gos2/) - very incomplete port to Go
* [s2-geometry-php](https://github.com/eelf/s2-geometry-library-php) - another very incomplete port to PHP
* [mapbox/node-s2](https://github.com/mapbox/node-s2)

## Thanks
* mapbox team
* [cypherix93](https://github.com/cypherix93)

## Contact Me 
[@billyriantono](http://twitter.com/kebluk_id) Feel free to contact me for help or anything else

