obj-m := hello.o  
KERNEL_DIR := /lib/modules/$(shell uname -r)/build  
PWD := $(shell pwd)  
all:  
    make -C $(KERNEL_DIR) $(PWD) modules  

clean:  
  
.PHONY:clean 
