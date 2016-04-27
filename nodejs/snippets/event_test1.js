#!/usr/bin/env node
const EventEmitter = require('events');
const util = require('util');

function MyEmitter(){
    EventEmitter.call(this);
}

util.inherits(MyEmitter, EventEmitter);


const myEmitter = new MyEmitter();

myEmitter.on('event', function(a,b){
    console.log(a, b, this);
});

myEmitter.on('test', (a, b)=>{
    setImmediate(()=>{
        console.log('this happends asynchronously');
    });
});


var m = 0;
myEmitter.once('sum', ()=>{
    console.log(++m);
})


process.on('uncaughtException', (err)=>{
    console.log('whoops! there was an erro');
});

myEmitter.once('newListener', (event, listener)=>{
    if (event === 'event2'){
        myEmitter.on('event2', ()=>{
            console.log('B')
        })
    }
})

myEmitter.on('event2', ()=>{
    console.log('A');
})

myEmitter.once('event3', ()=>{
    console.log('xxxxxxxxxxxxxxxxx');;
    console.log(myEmitter.getMaxListeners())

})


myEmitter.setMaxListeners(20)

myEmitter.emit('event', 1, 3);
myEmitter.emit('test', 3,4);

myEmitter.emit('event3');
myEmitter.emit('sum');
myEmitter.emit('sum');
myEmitter.emit('sum');
myEmitter.emit('event2');







