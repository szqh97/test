#!/usr/bin/env python
# -*- coding: utf-8 -*-

class Connection:
    def __init__(self):
        self.state = 'CLOSED'

    def read(self):
        if self.state != 'OPEN':
            raise RuntimeError('Not open')
        print ('reading...')

    def write(self, data):
        if self.state != 'OPEN':
            raise RuntimeError('Not Open')
        print ('writing...')

    def open(self):
        if self.state == 'OPEN':
            raise RuntimeError('Already open')
        self.state = 'OPEN'

    def close(self):
        if self.state =='CLOSED':
            raise RuntimeError('Already closed')
        self.state = 'CLOSED'

class Connection1:
    def __init__(self):
        self.new_state(ClosedConnectionState)

    def new_state(self, newstate):
        self._state = newstate

    def read(self):
        return self._state.read(self)

    def write(self, data):
        return self._state.write(self, data)

    def open(self):
        return self._state.open(self)

    def close(self):
        return self._state.close(self)


class ConnectionState:

    @staticmethod
    def read(conn):
        raise NotImplementedError()

    @staticmethod
    def write(conn, data):
        raise NotImplementedError()

    @staticmethod
    def open(conn):
        raise NotImplementedError()

    @staticmethod
    def close(conn):
        raise NotImplementedError()


class ClosedConnectionState(ConnectionState):
    
    @staticmethod
    def read(conn):
        raise RuntimeError('Not Open')

    @staticmethod
    def write(conn, data):
        raise RuntimeError('Not Open')

    @staticmethod
    def open(conn):
        conn.new_state(OpenConnectionState)

    @staticmethod
    def close(conn):
        raise RuntimeError('Already closed')


class OpenConnectionState(ConnectionState):
    @staticmethod
    def read(conn):
        print ('reading...')
    
    @staticmethod
    def write(conn, data):
        print ('writing')

    @staticmethod
    def open(conn):
        raise RuntimeError('Already open')

    @staticmethod
    def close(conn):
        conn.new_state(ClosedConnectionState)
