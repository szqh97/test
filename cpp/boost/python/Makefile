CC = g++
SHARED = -shared -o
FPIC = -fPIC 
LIBOBJECT = hello_ext.so

CPPFLAGS := ${CPPFLAGS} -g -I /usr/include/python2.7 -lboost_python
all: hello_ext getting_started1 getting_started2 std_pair

polymorphism_ext: polymorphism.o
	$(CC) polymorphism.o $(CPPFLAGS) $(FPIC) $(SHARED) polymorphism_ext.so 

voidptr_ext: voidptr.o
	$(CC) voidptr.o $(CPPFLAGS) $(FPIC) $(SHARED) voidptr_ext.so 

const_argument_ext: const_argument.o
	$(CC) const_argument.o $(CPPFLAGS) $(FPIC) $(SHARED) const_argument_ext.so 

list_ext: list.o
	$(CC) list.o $(CPPFLAGS) $(FPIC) $(SHARED) list_ext.so 

callbacks_ext: callbacks.o
	$(CC) callbacks.o $(CPPFLAGS) $(FPIC) $(SHARED) callbacks_ext.so 

object_ext: object.o
	$(CC) object.o $(CPPFLAGS) $(FPIC) $(SHARED) object_ext.so 

dict_ext: dict.o
	$(CC) dict.o $(CPPFLAGS) $(FPIC) $(SHARED) dict_ext.so 

args_ext: args.o
	$(CC) args.o $(CPPFLAGS) $(FPIC) $(SHARED) args_ext.so 

str_ext: str.o
	$(CC) str.o $(CPPFLAGS) $(FPIC) $(SHARED) str_ext.so 

class_ext: class.o
	$(CC) class.o $(CPPFLAGS) $(FPIC) $(SHARED) class_ext.so 

hello_ext: hello.o
	$(CC) hello.o $(CPPFLAGS) $(FPIC) $(SHARED) hello_ext.so 

getting_started1: getting_started1.o
	$(CC) getting_started1.o $(CPPFLAGS) $(FPIC) $(SHARED) getting_started1.so

getting_started2: getting_started2.o
	$(CC) getting_started2.o $(CPPFLAGS) $(FPIC) $(SHARED) getting_started2.so

std_pair: std_pair.o
	$(CC) std_pair.o $(CPPFLAGS) $(FPIC) $(SHARED) std_pair_ext.so

clean:
	rm -rf *.so
	rm -rf *.o
