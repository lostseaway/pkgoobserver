var Slack = require('slack-node');
var PokemonGO = require('./poke.io.js');
var socket = require('socket.io-client')('http://localhost:3001');
webhookUri = "https://hooks.slack.com/services/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";

var a = new PokemonGO.Pokeio();
slack = new Slack();
slack.setWebhook(webhookUri);

function sendNoti(text) {
  slack.webhook({
    channel: "#pkgo",
    username: "PKGoBot",
    icon_emoji: ":-_-:",
    text: text
  }, function(err, response) {
    // console.log(response);
  });
}

// function sendNoti(text){
//   console.log(text)
// }
var pokeStopName = {"d4d17ae9cc2b4b7e95cf84f07a0c4eca.11" : "Voice of Wind" , "77f731390077466fa267d5fce030e783.16" : "Nature Drive"}
var inMap = {}
var inStop = {}
socket.on('connect', function(){
  socket.emit('getLocation',{});
});

socket.on('nearby', function(msg){
  var pokemon = msg.pokemon

  pokemon.forEach(function(poke){
    updateWild(poke);
  })

  var pokestop = msg.pokestops
  pokestop.forEach(function(stop){
    if(parseFloat(stop.latitude) <= 13.743334 && parseFloat(stop.latitude) >=13.742354 && parseFloat(stop.longitude) >= 100.547344 && parseFloat(stop.longitude) <= 100.548709){
      if(pokeStopName[stop.pokestop_id] != null){
        if(inStop[stop.pokestop_id] == null) {
          inStop[stop.pokestop_id] = stop
          var lure = true
          if(stop.lure_expiration == 0) lure = false
          if(lure) sendNoti(pokeStopName[stop.pokestop_id] + " : Sakura start blooming!! (Someone actived Lure Module)")

          if(stop.active_pokemon_id != null) {
            sendNoti("Wild " + a.pokemonlist[stop.active_pokemon_id-1].name+" Appears!")
          }

        }
        else{
          if(stop.lure_expiration!=inStop[stop.pokestop_id].lure_expiration){
            if(stop.lure_expiration == 0) sendNoti(pokeStopName[stop.pokestop_id] + " : Lure Module has been ended!)")
            else if(inStop[stop.pokestop_id].lure_expiration == 0) sendNoti(pokeStopName[stop.pokestop_id] + " : Sakura start blooming!! (Someone actived Lure Module)")
          }
          if(stop.active_pokemon_id != inStop[stop.pokestop_id].active_pokemon_id) {
            if(stop.active_pokemon_id != null) sendNoti("Wild " + a.pokemonlist[stop.active_pokemon_id-1].name+" Appears!")
          }
          inStop[stop.pokestop_id] = stop
        }
      }
    }
  })

});

function updateWild(msg){
  if(inMap[msg.SpawnPointId] == null ){
    sendNoti("Wild " + a.pokemonlist[msg.PokedexTypeId-1].name+" Appears!")
    inMap[msg.SpawnPointId] = msg
  }
}
