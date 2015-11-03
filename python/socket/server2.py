#!/usr/bin/env python
# -*- coding: utf-8 -*-
import socket

EOL1 = b'\n\n'
EOL2 = b'\n\r\n'
response = b'HTTP/1.0 200 OK\r\nDate: Mon, 1 Jan 1996 01:01:01 GMT\r\n'
response += b'Content-Type: text/plain\r\nContent-Length: 13\r\n\r\n'
response += b'Hello, world!'
response='successful'

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serversocket.bind(('0.0.0.0', 5800))
serversocket.listen(1)

try:
    while True:
        connectionclient, address = serversocket.accept()
        request = b''
        #while EOL1 not in request and EOL2 not in request:
        #    request += connectionclient.recv(1024)
        request += connectionclient.recv(1024)
        print('-'*40 + '\n' + request.decode()[:-2])
        connectionclient.send(response)
        connectionclient.close()

except Exception, e:
    raise
finally:
    serversocket.close()
