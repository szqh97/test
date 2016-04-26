var WebTorrent = require('webtorrent')
var client = new WebTorrent()
var torrentId = '/tmp/t.torrent'

client.add(torrentId, function (torrent) {
    var file = torrent.files[0]
})
