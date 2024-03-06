#SHELL := /usr/bin/bash
obj-m += hello_module.o

CC := x86_64-linux-gnu-gcc-12

ifdef ARCH
	KDIR = /home/
else
	KDIR = /lib/modules/$(shell uname -r)/build
endif

all:
	make -C $(KDIR) M=$(shell pwd)  modules
clean:
	make -C $(KDIR) M=$(shell pwd)  clean