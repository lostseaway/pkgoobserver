var s2 = require('../');

var origin = new s2.S2CellId(new s2.S2LatLng(44.0378862, 10.0458712));

console.log(origin.parent(15).id());
console.log(origin.parent(15).child_end().id());

var latlng = new s2.S2LatLng(44.0378862, 10.0458712);
console.log(latlng.normalized().lat);
console.log(latlng.normalized().lng);

var origin = new s2.S2CellId(new s2.S2LatLng(37.7879938 ,-122.4074374));
console.dir(origin.parent(15).children());