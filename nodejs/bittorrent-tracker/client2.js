var Client = require('bittorrent-tracker').Client
var fs = require('fs')
var parseTorrent = require('parse-torrent')

var args = process.argv.splice(1);
var torrent_file_path = args[1];

var torrent = fs.readFileSync(torrent_file_path)
var parsedTorrent = parseTorrent(torrent) // { infoHash: 'xxx', length: xx, announce: ['xx', 'xx'] }

var peerId = new Buffer('01234567890123456789')
var port = 6881

var client = new Client(peerId, port, parsedTorrent)

// you must add an 'error' event handler!
client.on('error', function (err) {
  console.log(err.message)
  // a tracker was unavailable or sent bad data to the client. you can probably ignore it
})

// start getting peers from the tracker
client.start()

client.on('update', function (data) {
  console.log('got an announce response from tracker: ' + data.announce)
  console.log('number of seeders in the swarm: ' + data.complete)
  console.log('number of leechers in the swarm: ' + data.incomplete)
})

client.once('peer', function (addr) {
  console.log('found a peer: ' + addr) // 85.10.239.191:48623
})

// announce that download has completed (and you are now a seeder)
client.complete()

// force a tracker announce. will trigger more 'update' events and maybe more 'peer' events
client.update()

// stop getting peers from the tracker, gracefully leave the swarm
client.stop()

// scrape
client.scape()

client.on('scrape', function (data) {
  console.log('got a scrape response from tracker: ' + data.announce)
  console.log('number of seeders in the swarm: ' + data.complete)
  console.log('number of leechers in the swarm: ' + data.incomplete)
  console.log('number of total downloads of this torrent: ' + data.incomplete)
})
