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

var client = new WebTorrent();



