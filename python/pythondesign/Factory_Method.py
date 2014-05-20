#!/usr/bin/env python
import abc
import urllib2
from BeautifulSoup import BeautifulStoneSoup

class Connector(object):
    """ Abstract class to connect to remote resource """
    __metaclass__ = abc.ABCMeta # Decalre class as abstract class

    def __init__(self, is_secure):
        self.is_secure = is_secure
        self.port = self.port_factory_method()
        self.protocal = self.protocal_factory_method()

    @abc.abstractmethod
    def parse(self):
        """ Parse web content.
        This method should be redfined in the runtime ."""
        pass

    def read(self, host, path):
        """ A generic method for all subclasses, reads web contnt. """
        url = self.protocal + "://" + host + ":" + str(self.port) + path
        print "Connecting to ", url
        return urllib2.urlopen(url, timeout = 2).read()

    @abc.abstractmethod
    def protocal_factory_method(self):
        """ A factory method that must be redfined in subclass. """
        pass

    @abc.abstractmethod
    def port_factory_method(self):
        """ A factory method that must be redfined in subclass. """
        return FTPPort()

class HTTPConnector(Connector):
    """ A concrete creator that creates a HTTP conncetor and sets in 
    runtime all its attributes. """

    def protocal_factory_method(self):
        if self.is_secure:
            return "https"
        return "http"

    def port_factory_method(self):
        """ Here HTTPPort and HTTPSecurePort are concrete objects, 
        created by factory method. """
        if self.is_secure:
            return HTTPSecurePort()
        return HTTPPort()

    def parse(self, contnt):
        """ Parse web content """
        filenames = []
        soup = BeautifulStoneSoup(content)
        links = soup.table.findAll('a')
        for link in links:
            filenames.append(link['href'])
        return '\n'.join(filenames)

