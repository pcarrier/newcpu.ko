obj-m += newcpu.o

all:
	make -C /lib/modules/3.3.7-1-ck/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
