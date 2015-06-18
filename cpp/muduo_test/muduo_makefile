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

all: echo

clean:
	rm -f echo core

echo: $(SRC)/muduo_echoserver.cpp
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean
