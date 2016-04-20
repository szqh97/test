#!/usr/bin/env node
var WebTorrent = require('webtorrent')
var opts = {
    announce: [   
        'wss://tracker.btorrent.xyz',
    'wss://tracker.fastcast.nz',
    'wss://tracker.openwebtorrent.com',
    'wss://tracker.webtorrent.io',
    'ws://wstracker.vuze.com:8000/'
        ],
}

var slices = process.argv.splice(2)
var torrentId = slices[0]
var timeout = slices[1]
var client = new WebTorrent();
var torrent = client.add(torrentId, opts);
torrent.on('wire', function (wire, addr){
    console.log(torrent.infoHash,  ' conected to peer with address:',addr )
});


var port=8000
server = torrent.createServer();

server.listen(port, initServer)
.on('error', function (err) {
  if (err.code === 'EADDRINUSE' || err.code === 'EACCES') {
    // If port is taken, pick one a free one automatically
    return server.listen(0, initServer)
  }
  //fatalError(err)
})


function initServer () {
    if (torrent.ready) onReady()
    else torrent.once('ready', onReady)
};

function onReady(){
    drawTorrent(torrent)
}

function drawTorrent(torrent){
    //console.log(torrent)
}


setTimeout(function () { process.exit(0) }, timeout *1000);

