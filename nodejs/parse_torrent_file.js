var fs = require('fs')
var parseTorrent = require('parse-torrent')
var args = process.argv.splice(1);
var torrent_file_path = args[1];
var torrent = fs.readFileSync(torrent_file_path);

var parsedTorrent = parseTorrent(torrent);
parsedTorrent.pieces= ['...']
console.log(parsedTorrent)


