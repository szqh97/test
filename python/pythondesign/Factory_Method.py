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


class FTPConnector(Connector):
    """ A concrete createor that creates a FTP connector and sets in  
    runtime all its attributes. """

    def protocal_factory_method(self):
        return "ftp"

    def port_factory_method(self):
        return FTPPort()

    def parse(self, content):
        lines = content.seplit('\n')
        filenames = []
        for line in lines:
            #The ftp fromat typically has a 8colums, split them 
            splited_line = line.split(None, 8)
            if len(splited_line) == 9:
                filenames.append(splited_line[-1])

        return '\n'.joing(filenames)

class Port(object):
    __metaclass__ = abc.ABCMeta
    """ Abstract product. one of its subclasses will be created in factory methods. """

    @abc.abstractmethod
    def __str__(self):
        pass

class HTTPPort(Port):
    """ A concrete product which represents http port. """

    def __str(self):
        return "80"

class HTTPSecureProt(Port):
    """ a CONCRETE product which represents https port."""
    def __str__(self):
        return "443"

class FTPPort(self):
    """ A concrete product which represents ftp port."""
    def __str__(self):
        return "21"

if __name__ == '__main__':
    domain = 'ftp.freebsd.org'
    path = '/pub/FreeBSD/'

    protocol = input("Connecting to {}, which Protocol to use? (0-http, 1-ftp): ".format(domain))

    if protocol == 0:
        is_secure = bool(input("Use secure connection? (1-yes, 0-no): "))
        connector = HTTPConnector(is_secure)
    else:
        is_secure = False
        connector = FTPConnector(is_secure)

    try:
        content = connector.read(domain, path)
    except urllib2.URLError, e:
        print "Can not access resource with this method"
    else:
        print connector.parse(content)
