➜  tornado-celery git:(master) sudo python setup.py install
running install
running bdist_egg
running egg_info
creating tornado_celery.egg-info
writing requirements to tornado_celery.egg-info/requires.txt
writing tornado_celery.egg-info/PKG-INFO
writing top-level names to tornado_celery.egg-info/top_level.txt
writing dependency_links to tornado_celery.egg-info/dependency_links.txt
writing entry points to tornado_celery.egg-info/entry_points.txt
writing manifest file 'tornado_celery.egg-info/SOURCES.txt'
reading manifest file 'tornado_celery.egg-info/SOURCES.txt'
reading manifest template 'MANIFEST.in'
writing manifest file 'tornado_celery.egg-info/SOURCES.txt'
installing library code to build/bdist.linux-i686/egg
running install_lib
running build_py
creating build
creating build/lib.linux-i686-2.7
creating build/lib.linux-i686-2.7/examples
copying examples/tasks.py -> build/lib.linux-i686-2.7/examples
copying examples/__init__.py -> build/lib.linux-i686-2.7/examples
copying examples/tornado_ioloop.py -> build/lib.linux-i686-2.7/examples
copying examples/tornado_async.py -> build/lib.linux-i686-2.7/examples
creating build/lib.linux-i686-2.7/tcelery
copying tcelery/redis.py -> build/lib.linux-i686-2.7/tcelery
copying tcelery/__init__.py -> build/lib.linux-i686-2.7/tcelery
copying tcelery/app.py -> build/lib.linux-i686-2.7/tcelery
copying tcelery/producer.py -> build/lib.linux-i686-2.7/tcelery
copying tcelery/connection.py -> build/lib.linux-i686-2.7/tcelery
copying tcelery/handlers.py -> build/lib.linux-i686-2.7/tcelery
copying tcelery/utils.py -> build/lib.linux-i686-2.7/tcelery
copying tcelery/__main__.py -> build/lib.linux-i686-2.7/tcelery
copying tcelery/result.py -> build/lib.linux-i686-2.7/tcelery
creating build/bdist.linux-i686
creating build/bdist.linux-i686/egg
creating build/bdist.linux-i686/egg/examples
copying build/lib.linux-i686-2.7/examples/tasks.py -> build/bdist.linux-i686/egg/examples
copying build/lib.linux-i686-2.7/examples/__init__.py -> build/bdist.linux-i686/egg/examples
copying build/lib.linux-i686-2.7/examples/tornado_ioloop.py -> build/bdist.linux-i686/egg/examples
copying build/lib.linux-i686-2.7/examples/tornado_async.py -> build/bdist.linux-i686/egg/examples
creating build/bdist.linux-i686/egg/tcelery
copying build/lib.linux-i686-2.7/tcelery/redis.py -> build/bdist.linux-i686/egg/tcelery
copying build/lib.linux-i686-2.7/tcelery/__init__.py -> build/bdist.linux-i686/egg/tcelery
copying build/lib.linux-i686-2.7/tcelery/app.py -> build/bdist.linux-i686/egg/tcelery
copying build/lib.linux-i686-2.7/tcelery/producer.py -> build/bdist.linux-i686/egg/tcelery
copying build/lib.linux-i686-2.7/tcelery/connection.py -> build/bdist.linux-i686/egg/tcelery
copying build/lib.linux-i686-2.7/tcelery/handlers.py -> build/bdist.linux-i686/egg/tcelery
copying build/lib.linux-i686-2.7/tcelery/utils.py -> build/bdist.linux-i686/egg/tcelery
copying build/lib.linux-i686-2.7/tcelery/__main__.py -> build/bdist.linux-i686/egg/tcelery
copying build/lib.linux-i686-2.7/tcelery/result.py -> build/bdist.linux-i686/egg/tcelery
byte-compiling build/bdist.linux-i686/egg/examples/tasks.py to tasks.pyc
byte-compiling build/bdist.linux-i686/egg/examples/__init__.py to __init__.pyc
byte-compiling build/bdist.linux-i686/egg/examples/tornado_ioloop.py to tornado_ioloop.pyc
byte-compiling build/bdist.linux-i686/egg/examples/tornado_async.py to tornado_async.pyc
byte-compiling build/bdist.linux-i686/egg/tcelery/redis.py to redis.pyc
byte-compiling build/bdist.linux-i686/egg/tcelery/__init__.py to __init__.pyc
byte-compiling build/bdist.linux-i686/egg/tcelery/app.py to app.pyc
byte-compiling build/bdist.linux-i686/egg/tcelery/producer.py to producer.pyc
byte-compiling build/bdist.linux-i686/egg/tcelery/connection.py to connection.pyc
byte-compiling build/bdist.linux-i686/egg/tcelery/handlers.py to handlers.pyc
byte-compiling build/bdist.linux-i686/egg/tcelery/utils.py to utils.pyc
byte-compiling build/bdist.linux-i686/egg/tcelery/__main__.py to __main__.pyc
byte-compiling build/bdist.linux-i686/egg/tcelery/result.py to result.pyc
creating build/bdist.linux-i686/egg/EGG-INFO
copying tornado_celery.egg-info/PKG-INFO -> build/bdist.linux-i686/egg/EGG-INFO
copying tornado_celery.egg-info/SOURCES.txt -> build/bdist.linux-i686/egg/EGG-INFO
copying tornado_celery.egg-info/dependency_links.txt -> build/bdist.linux-i686/egg/EGG-INFO
copying tornado_celery.egg-info/entry_points.txt -> build/bdist.linux-i686/egg/EGG-INFO
copying tornado_celery.egg-info/requires.txt -> build/bdist.linux-i686/egg/EGG-INFO
copying tornado_celery.egg-info/top_level.txt -> build/bdist.linux-i686/egg/EGG-INFO
zip_safe flag not set; analyzing archive contents...
creating dist
creating 'dist/tornado_celery-0.3.5-py2.7.egg' and adding 'build/bdist.linux-i686/egg' to it
removing 'build/bdist.linux-i686/egg' (and everything under it)
Processing tornado_celery-0.3.5-py2.7.egg
Copying tornado_celery-0.3.5-py2.7.egg to /usr/local/lib/python2.7/dist-packages
Adding tornado-celery 0.3.5 to easy-install.pth file
Installing tcelery script to /usr/local/bin

Installed /usr/local/lib/python2.7/dist-packages/tornado_celery-0.3.5-py2.7.egg
Processing dependencies for tornado-celery==0.3.5
Searching for pika
Reading https://pypi.python.org/simple/pika/
Best match: pika 0.9.14
Downloading https://pypi.python.org/packages/source/p/pika/pika-0.9.14.tar.gz#md5=b99aad4b88961d3c7e4876b8327fc97c
Processing pika-0.9.14.tar.gz
Writing /tmp/easy_install-kWsmoN/pika-0.9.14/setup.cfg
Running pika-0.9.14/setup.py -q bdist_egg --dist-dir /tmp/easy_install-kWsmoN/pika-0.9.14/egg-dist-tmp-yUeHHS
Adding pika 0.9.14 to easy-install.pth file

Installed /usr/local/lib/python2.7/dist-packages/pika-0.9.14-py2.7.egg
Searching for celery
Reading https://pypi.python.org/simple/celery/
Best match: celery 3.1.18
Downloading https://pypi.python.org/packages/source/c/celery/celery-3.1.18.tar.gz#md5=1c25973250f75788fb9c690d4fc68957
Processing celery-3.1.18.tar.gz
Writing /tmp/easy_install-Yo2KVV/celery-3.1.18/setup.cfg
Running celery-3.1.18/setup.py -q bdist_egg --dist-dir /tmp/easy_install-Yo2KVV/celery-3.1.18/egg-dist-tmp-ieqM8d
- Trying to upgrade 'task' in 'celery.app'
- upgrade task: no old version found.
no previously-included directories found matching '*.pyc'
no previously-included directories found matching '*.sw*'
Adding celery 3.1.18 to easy-install.pth file
Installing celery script to /usr/local/bin
Installing celeryd script to /usr/local/bin
Installing celeryd-multi script to /usr/local/bin
Installing celerybeat script to /usr/local/bin

Installed /usr/local/lib/python2.7/dist-packages/celery-3.1.18-py2.7.egg
Searching for kombu>=3.0.25,<3.1
Reading https://pypi.python.org/simple/kombu/
Best match: kombu 3.0.26
Downloading https://pypi.python.org/packages/source/k/kombu/kombu-3.0.26.tar.gz#md5=dda05763cd4b72a131fe1ef9ba93d542
Processing kombu-3.0.26.tar.gz
Writing /tmp/easy_install-r8lVeZ/kombu-3.0.26/setup.cfg
Running kombu-3.0.26/setup.py -q bdist_egg --dist-dir /tmp/easy_install-r8lVeZ/kombu-3.0.26/egg-dist-tmp-R11pDy
warning: no files found matching 'README'
Adding kombu 3.0.26 to easy-install.pth file

Installed /usr/local/lib/python2.7/dist-packages/kombu-3.0.26-py2.7.egg
Searching for billiard>=3.3.0.20,<3.4
Reading https://pypi.python.org/simple/billiard/
Best match: billiard 3.3.0.20
Downloading https://pypi.python.org/packages/source/b/billiard/billiard-3.3.0.20.tar.gz#md5=2cb556e5390fa922a8d6a56149ac8f0c
Processing billiard-3.3.0.20.tar.gz
Writing /tmp/easy_install-OIybvm/billiard-3.3.0.20/setup.cfg
Running billiard-3.3.0.20/setup.py -q bdist_egg --dist-dir /tmp/easy_install-OIybvm/billiard-3.3.0.20/egg-dist-tmp-XNU3Bp
warning: no files found matching '*.py' under directory 'Lib'
Adding billiard 3.3.0.20 to easy-install.pth file

Installed /usr/local/lib/python2.7/dist-packages/billiard-3.3.0.20-py2.7-linux-i686.egg
Searching for pytz>dev
Reading https://pypi.python.org/simple/pytz/
Best match: pytz 2015.4
Downloading https://pypi.python.org/packages/2.7/p/pytz/pytz-2015.4-py2.7.egg#md5=4698c08f18f5cecba09b7e85d8e9328e
Processing pytz-2015.4-py2.7.egg
Moving pytz-2015.4-py2.7.egg to /usr/local/lib/python2.7/dist-packages
Adding pytz 2015.4 to easy-install.pth file

Installed /usr/local/lib/python2.7/dist-packages/pytz-2015.4-py2.7.egg
Searching for amqp>=1.4.6,<2.0
Reading https://pypi.python.org/simple/amqp/
Best match: amqp 1.4.6
Downloading https://pypi.python.org/packages/source/a/amqp/amqp-1.4.6.tar.gz#md5=a061581b6864f838bffd62b6a3d0fb9f
Processing amqp-1.4.6.tar.gz
Writing /tmp/easy_install-oUxyZN/amqp-1.4.6/setup.cfg
Running amqp-1.4.6/setup.py -q bdist_egg --dist-dir /tmp/easy_install-oUxyZN/amqp-1.4.6/egg-dist-tmp-SwYm6p
Adding amqp 1.4.6 to easy-install.pth file

Installed /usr/local/lib/python2.7/dist-packages/amqp-1.4.6-py2.7.egg
Searching for anyjson>=0.3.3
Reading https://pypi.python.org/simple/anyjson/
Best match: anyjson 0.3.3
Downloading https://pypi.python.org/packages/source/a/anyjson/anyjson-0.3.3.tar.gz#md5=2ea28d6ec311aeeebaf993cb3008b27c
Processing anyjson-0.3.3.tar.gz
Writing /tmp/easy_install-eHMRSr/anyjson-0.3.3/setup.cfg
Running anyjson-0.3.3/setup.py -q bdist_egg --dist-dir /tmp/easy_install-eHMRSr/anyjson-0.3.3/egg-dist-tmp-onC9ae
Adding anyjson 0.3.3 to easy-install.pth file

Installed /usr/local/lib/python2.7/dist-packages/anyjson-0.3.3-py2.7.egg
Searching for tornado==4.2
Best match: tornado 4.2
Processing tornado-4.2-py2.7-linux-i686.egg
tornado 4.2 is already the active version in easy-install.pth

Using /usr/local/lib/python2.7/dist-packages/tornado-4.2-py2.7-linux-i686.egg
Searching for certifi==2015.04.28
Best match: certifi 2015.04.28
Processing certifi-2015.04.28-py2.7.egg
certifi 2015.04.28 is already the active version in easy-install.pth

Using /usr/local/lib/python2.7/dist-packages/certifi-2015.04.28-py2.7.egg
Searching for backports.ssl-match-hostname==3.4.0.2
Best match: backports.ssl-match-hostname 3.4.0.2
Processing backports.ssl_match_hostname-3.4.0.2-py2.7.egg
backports.ssl-match-hostname 3.4.0.2 is already the active version in easy-install.pth

Using /usr/local/lib/python2.7/dist-packages/backports.ssl_match_hostname-3.4.0.2-py2.7.egg
Finished processing dependencies for tornado-celery==0.3.5
