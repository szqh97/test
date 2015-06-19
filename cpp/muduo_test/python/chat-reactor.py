#!/usr/bin/env python
import socket
import select
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR, 1)
server_socket.bind(('', 2007))
server_socket.listen(5)


poll = select.poll()
connections = {}
handlers = {}


def handle_input(socket, data):
    for(fd, other_socket) in connections.iteritems():
        if other_socket != socket:
            other_socket.send('recv: ' + data)
        else:
            socket.send('send: ' + data)

def handle_request(fineno, event):
    if event & select.POLLIN:
        client_socket = connections[fineno]
        data = client_socket.recv(4096)
        if data:
            #client_socket.send(data)
            handle_input(client_socket, data)
        else:
            poll.unregister(fineno)
            client_socket.close()
            del connections[fineno]
            del handlers[fineno]

def handle_accept(fileno, event):
    (client_socket, client_address) = server_socket.accept()
    print 'go connection from ', client_address
    poll.register(client_socket.fileno(), select.POLLIN)
    connections[client_socket.fileno()] = client_socket
    handlers[client_socket.fileno()] = handle_request

poll.register(server_socket.fileno(), select.POLLIN)
handlers[server_socket.fileno()] = handle_accept

while True:
    events = poll.poll(10000)
    for fileno, event in events:
        h = handlers[fileno]
        h(fileno, event)

