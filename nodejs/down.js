var WebTorrent = require('webtorrent')
var fs = require('fs')

var client = new WebTorrent()

var magnetURI = 'magnet:?xt=urn:btih:6a9759bffd5c0af65319979fb7832189f4f3c35d&dn=sintel.mp4&tr=wss%3A%2F%2Ftracker.btorrent.xyz&tr=wss%3A%2F%2Ftracker.fastcast.nz&tr=wss%3A%2F%2Ftracker.openwebtorrent.com&tr=wss%3A%2F%2Ftracker.webtorrent.io&ws=https%3A%2F%2Fwebtorrent.io%2Ftorrents%2Fsintel-1024-surround.mp4'

client.add(magnetURI, function (torrent) {
  torrent.files.forEach(function (file) {
    console.log('Started saving ' + file.name)

    file.getBuffer(function (err, buffer) {
      if (err) {
        console.error('Error downloading ' + file.name)
        return
      }
      fs.writeFile(file.name, buffer, function (err) {
        console.error('Error saving ' + file.name)
      })
    })
  })
})

