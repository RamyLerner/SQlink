# this is a minimal makefile for demo purposes, keep it that way...
obj-m:=messageQ.o
messageQ-objs:=main.o
V?=0
KDIR?=/lib/modules/$(shell uname -r)/build
# in an embedded system:
#KDIR:=[where the system maker gave me kernel headers+makefile or the kernel itself which has a makefile]
#ARCH:=arm
#CROSS_COMPILE:=[path+common prefix to where the toolchain is]
# You could also use W=2 and W=3 for more warnings but most kernel headers
# fail those...
W?=1
.PHONY: modules
modules:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) W=$(W) modules
.PHONY: clean
clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) clean
	rm -f *.stamp

.PHONY: insmod
insmod:
	sudo insmod ./messageQ.ko
	sleep 1
	sudo chmod 666 /dev/messageQ*

.PHONY: rmmod
rmmod:
	sudo rmmod messageQ

.PHONY: remod
remod: rmmod insmod

test : test_basic test_waiting test_lock_thread test_lock_proccess

test_basic : test_basic.c 
	gcc -pedantic -ansi -O2 -o $@ $<

test_waiting : test_waiting.c
	gcc -pedantic -ansi -O2 -pthread -o $@ $<

test_lock_thread : test_lock_thread.c
	gcc -pedantic -ansi -O2 -pthread -o $@ $<

test_lock_proccess : test_lock_proccess.c
	gcc -pedantic -ansi -O2 -pthread -o $@ $<


test_multi_ins:
	for i in $$(seq 0 80);\
	do \
	sudo insmod ./messageQ.ko;\
	sudo rmmod messageQ;\
	echo $$i;\
	done

test_dif_dev : test_dif_dev.c
	gcc -pedantic -ansi -O2 -pthread -o $@ $<
	for i in $$(seq 0 7);\
	do \
	./test_dif_dev /dev/messageQ$$i;\
	echo test of /dev/messageQ$$i successful;\
	done

