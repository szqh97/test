#!/usr/bin/env node
var fs =  require('fs')
fs.readFile('/tmp/t', function(err, file){
    console.log('read file 1 ok');
});
fs.readFile('/tmp/ttt', function(err, file){
    console.log('read file 2 ok');
});
