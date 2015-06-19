#!/usr/bin/env python
import socket
import select
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind(('0.0.0.0', 2007))
server_socket.listen(5)
poll = select.poll()
poll.register(server_socket.fileno(), select.POLLIN)

connections = {}
while True:
    events = poll.poll(10000)
    for fileno, event in events:
        if fileno == server_socket.fileno():
            (client_socket, client_address) = server_socket.accept()
            print "got connection from " , client_address
            poll.register(client_socket.fileno(), select.POLLIN)
            connections[client_socket.fileno()] = client_socket
        elif event & select.POLLIN:
            client_socket = connections[fileno]
            data = client_socket.recv(4096)
            if data:
                for (fd, othersocket) in connections.iteritems():
                    if othersocket != client_socket:
                        othersocket.send('recv: ' + data)
                    else:
                        client_socket.send('send: ' + data)

            else:
                poll.unregister(fileno)
                client_socket.close()
                del connections[fileno]


