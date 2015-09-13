#!/usr/bin/env python
# -*- coding: utf-8 -*-
import socket
import select

EOL1 = b'\n\n'
EOL2 = b'\n\r\n'
response = b'HTTP/1.0 200 OK\r\nDate: Mon, 1 Jan 1996 01:01:01 GMT\r\n'
response += b'Content-Type: text/plain\r\nContent-Length: 13\r\n\r\n'
response += b'Hello, world!\n\n'

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serversocket.bind(('0.0.0.0', 8899))
serversocket.listen(1)
serversocket.setblocking(0)

epoll = select.epoll()
epoll.register(serversocket.fileno(), select.EPOLLIN | select.EPOLLET)

try:
    connections = {}
    requests = {}
    responses = {}
    while True:
        events = epoll.poll(1)
        for fileno, event in events:
            if fileno == serversocket.fileno():
                try:
                    while True:
                        connection, address = serversocket.accept()
                        connection.setblocking(0)
                        epoll.register(connection.fileno(), select.EPOLLET | select.EPOLLIN)
                        connections[connection.fileno()] = connection
                        requests[connection.fileno()] = b''
                        responses[connection.fileno()] = response
                except socket.error:
                    raise 
            elif event & select.EPOLLIN:
                try:
                    while True:
                        requests[fileno] += connections[fileno].recv(1024)
                except Exception, e:
                    raise e
                if EOL1 in requests[fileno] or EOL2 in requests[fileno]:
                    epoll.modify(fileno, select.EPOLLOUT | select.EPOLLET)
                    print('-'*34 + '\n' + requests[fileno].decode()[:-2])
            elif event & select.EPOLLOUT:
                try:
                    while len(responses[fileno]) > 0:
                        byteswritten = connections[fileno].send(responses[fileno])
                        responses[fileno] = responses[fileno][byteswritten:]
                except socket.error:
                    pass
                if len(responses[fileno]) == 0:
                    epoll.modify(fileno, select.EPOLLET) 
                    connections[fileno].shutdown(socket.SHUT_RDWR)
            elif event & select.EPOLLHUP:
                epoll.unregister(fileno)
                connections[fileno].close()
                del connections[fileno]

except Exception, e:
    raise e

finally:
    epoll.unregister(serversocket.fileno())
    epoll.close()
    serversocket.close()
