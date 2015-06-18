MUDUO_DIRECTORY ?= $(HOME)/build/debug-install

#MUDUO_DIRECTORY ?= $(HOME)/build/install

MUDUO_INCLUDE = /home/li_yun/Projects/build/release-install/include

MUDUO_LIBRARY = /home/li_yun/Projects/build/release-install/lib 

SRC = .

CXXFLAGS = -g -O0 -Wall -Wextra -Werror \
		   -Wconversion -Wno-unused-parameter \
		   -Wold-style-cast -Woverloaded-virtual \
		   -Wpointer-arith -Wshadow -Wwrite-strings \
		   -march=native -rdynamic \
		   -I$(MUDUO_INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt

all: echo finger01 finger02 finger03 finger04 finger06 \
	 finger07

clean:
	rm -f echo core finger01 finger02
	ls -F |grep \*|sed -e 's/\*//g' |xargs rm -rf

echo: $(SRC)/muduo_echoserver.cpp
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

finger01: finger01.cpp
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

finger02: finger02.cpp
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

finger03: finger03.cpp
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

finger04: finger04.cpp
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

finger06: finger06.cpp
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

finger07: finger07.cpp
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean
