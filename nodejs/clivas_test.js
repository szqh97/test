#!/usr/bin/env node

var clivas = require('clivas')
clivas.line('{red:i am red} and {blue: i am blue}');
clivas.line('{red+inverse:i am inversed}');
clivas.line('[{10:===>}]'); // prints [===>      ]
