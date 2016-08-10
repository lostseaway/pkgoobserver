'use strict';

var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var PokemonGO = require('./poke.io.js');
var currentUsers = {};

app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

app.get('/json', function(req, res){
  res.sendFile(__dirname + '/pokemons.json');
});

io.on('connection', function(socket){
  console.log('a user connected');
  if(currentUsers[socket.id] == null) {
    currentUsers[socket.id] = {"socket": socket}
  }

  socket.on("getLocation",function(){
    socket.emit("bLocation",{ name :locationName, lat:latitude , lng:longitude })
    socket.emit("bGyms",{gyms:gymsDetail})
  })

  socket.on('disconnect', function(){
    console.log('user disconnected');
    currentUsers[socket.id] = null
  });
});

http.listen(3001, function(){
  console.log('listening on *:3001');
});

var a = new PokemonGO.Pokeio();
var locationName = ""
var latitude = 13.7425462;
var longitude = 100.547885;
//Set environment variables or replace placeholder text
var location = {
    type: 'coords',
    coords: {
        latitude: latitude,
        longitude: longitude,
        altitude: 0
    }
};

var username = process.env.PGO_USERNAME || '';
var password = process.env.PGO_PASSWORD || '';
var provider = process.env.PGO_PROVIDER || 'google';

var gymsDetail = []
var gymsID = []
var ch = 0
a.init(username, password, location, provider, function(err) {
    if (err) throw err;

    a.GetProfile(function(err, profile) {
        if (err) throw err;
        locationName = a.playerInfo.locationName
        setInterval(function(){
            a.Heartbeat(function(err,hb) {
                if(err) {
                    console.log(err);
                }else{
                var pokemons = [];
                var pokestops = [];
                var gyms = [];
                hb.cells.forEach(function (cell) {
                   cell.Fort.forEach(function (fort) {
                     if (null === fort.FortType || 0 === fort.FortType) {
                       gyms.push({
                         gym_id: fort.FortId
                       , gym_points: fort.GymPoints
                       , enabled: fort.Enabled
                       , guard_pokemon_id: fort.GuardPokemonId
                       , guard_pokemon_level: fort.GuardPokemonLevel
                       , last_modified: parseInt(fort.LastModifiedMs
                           && fort.LastModifiedMs.toString() || 0, 10) || 0
                       , latitude: fort.Latitude
                       , longitude: fort.Longitude
                       , team_id: fort.Team
                       });
                       if(gymsID.indexOf(fort.FortId) == -1){
                         a.GetFortDetails(fort.FortId,fort.Latitude,fort.Longitude,function(err,msg){
                           if(err) {
                               console.log(err);
                           }else{
                              gymsID.push(fort.FortId)
                              gymsDetail.push(msg)
                           }

                         })
                       }

                     }
                     else if (1 === fort.FortType) {
                       pokestops.push({
                         pokestop_id: fort.FortId
                       , active_pokemon_id: fort.LureInfo
                           && fort.LureInfo.ActivePokemonId || null
                       , enabled: fort.Enabled
                       , last_modified: parseInt(fort.LastModifiedMs
                           && fort.LastModifiedMs.toString() || 0, 10) || 0
                       , latitude: fort.Latitude
                       , longitude: fort.Longitude
                       , lure_expiration: parseInt(fort.LureInfo
                           && fort.LureInfo.LureExpiresTimestampMs
                           && fort.LureInfo.LureExpiresTimestampMs.toString() || 0, 10) || 0
                       });
                     }
                     else {
                       console.log('Unknown Fort Type:');
                       console.log(fort);
                     }
                   });
                // var wildpokemon = []
                for (var i = hb.cells.length - 1; i >= 0; i--) {
                    if(hb.cells[i].MapPokemon[0]) {
                      for(var j = hb.cells[i].MapPokemon.length - 1; j >= 0 ;j -- ){
                        pokemons.push(hb.cells[i].MapPokemon[j]);
                      }
                    }
                }
                // ch = 1;
                io.sockets.emit('nearby', {pokemon: pokemons,pokestops: pokestops, gyms: gyms});
              })
            }
          });

        }, 5000);
    });

    // a.GetFortDetails("d4d17ae9cc2b4b7e95cf84f07a0c4eca.11",13.742873,100.547678,function(err, msg){
    //   console.log(msg)
    // })
});
