var s2 = require('../');
var assert = require('assert');

describe('s2', function () {
    it("should export a function that calculates the distance between two points on the earth's surface", function () {
        var los_angeles = {lat: 34.0522, long: 118.2437}
        var new_york = {lat: 40.7128, long: 74.0059}
        var dist = new s2.S2CellId(new s2.S2LatLng(los_angeles.lat, los_angeles.long)).level(15).parent();
        var actual = 3940163 // floor of actual
        console.dir(dist)
        assert(typeof dist === 'number')
        //assert(dist >= actual && dist <= actual + 1)
    });

    it("should throw when calling DistanceBetweenLocations with missing arguments", function () {
        try {
            s2.DistanceBetweenLocations()
        } catch (e) {
            assert(true)
            return
        }
        assert(false)
    })

    it("should export a function that calculates the level given a desired edge length in meters", function () {
        var level = s2.GetClosestLevel(1000)
        // console.log(level)
        assert(typeof level === 'number')
        assert(level === 13)
    });

    it("should throw when calling GetClosestLevel with missing arguments", function () {
        try {
            s2.GetClosestLevel()
        } catch (e) {
            assert(true)
            return
        }
        assert(false)
    })

    it("should export a function that calculates the cell at a given location and level", function () {
        var los_angeles = {lat: 34.0522, long: 118.2437}
        var level = s2.GetClosestLevel(1000)
        var cell = s2.CellAtLocationAndLevel(los_angeles.lat, los_angeles.long, level)
        // console.log(cell)
        assert(Buffer.isBuffer(cell))
        assert(cell.length === 8)
        assert(cell.equals(new Buffer('000000001cc3c735', 'hex')))
    });

    it("should throw when calling CellAtLocationAndLevel with missing arguments", function () {
        try {
            s2.CellAtLocationAndLevel()
        } catch (e) {
            assert(true)
            return
        }
        assert(false)
    })

    it("should export a function that calculates the cell ranges to search for a given lat/long, distance, and min/max level combination", function () {
        var los_angeles = {lat: 34.0522, long: 118.2437}
        var min_level = s2.GetClosestLevel(100000)
        var max_level = s2.GetClosestLevel(1000)
        // console.log('min_level', min_level)
        // console.log('max_level', max_level)
        var distance = 5000
        var ranges = s2.SearchRanges(los_angeles.lat, los_angeles.long, distance, min_level, max_level)
        // console.log(ranges.length)
        // console.log(ranges)
        assert(Array.isArray(ranges))
        assert(ranges.length <= 40)
        ranges.forEach(function (cell) {
            assert(Buffer.isBuffer(cell))
            assert(cell.length === 8)
        })
    });

    it("should throw when calling SearchRanges with missing arguments", function () {
        try {
            s2.SearchRanges()
        } catch (e) {
            assert(true)
            return
        }
        assert(false)
    })

    it("should walk", function () {
        // var los_angeles = {lat: 34.0522, long: 118.2437}
         var origin = new s2.S2CellId(new s2.S2LatLng(44.0378862, 10.0458712));
        // // var walk = [origin.id()];
        // var next = origin.next()
        // // prev = origin.prev()
        // // for i in range(10):
        // // walk.append(prev.id())
        // // walk.append(next.id())
        // // next = next.next()
        // // prev = prev.prev()
        //var ll = new s2.S2LatLng(40, 20);//.toPoint();

        //var normalized = ll.normalized(); // true
        //var pt = ll.toString();
        //console.dir(pt);
         console.dir(origin.parent());

        assert(false);

    })

});
