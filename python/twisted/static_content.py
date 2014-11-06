from twisted.internet import reactor
from twisted.web.server import Site
from twisted.web.static import File

resource = File('/var/www/')
factory = Site(resource)
reactor.listenTCP(8000, factory)
reactor.run()
