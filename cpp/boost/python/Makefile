CC = g++
SHARED = -shared -o
FPIC = -fPIC 
LIBOBJECT = hello_ext.so

CPPFLAGS := ${CPPFLAGS} -g -I /usr/include/python2.7 -lboost_python
all: hello_ext getting_started1 getting_started2

hello_ext: hello.o
	$(CC) hello.o $(CPPFLAGS) $(FPIC) $(SHARED) hello_ext.so 

getting_started1: getting_started1.o
	$(CC) getting_started1.o $(CPPFLAGS) $(FPIC) $(SHARED) getting_started1.so

getting_started2: getting_started2.o
	$(CC) getting_started2.o $(CPPFLAGS) $(FPIC) $(SHARED) getting_started2.so

clean:
	rm -rf *.so
	rm -rf *.o
