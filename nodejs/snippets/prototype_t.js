#!/usr/bin/env node
var toString = Object.prototype.toString;
    
var isString = function (obj) {
    return toString.call(obj) == '[object String]';
};
var isFunction = function (obj) {
    return toString.call(obj) == '[object function]';
}

var isType = function (type) {
    return function (obj) {
        return toString.call(obj) == '[object ' + type + ']';
    };
};


