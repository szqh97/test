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

var torrentId = process.argv.splice(2)[0]
var client = new WebTorrent();
var torrent = client.add(torrentId, opts)
console.log(torrent);
torrent.on('wire', function (wire, addr){
    console.log('conected to peer with address:',addr )
})

setTimeout(function () { process.exit(0) }, 1000)

