# XTL - the eXternalization Template Library (sample code)
# by Jose' Orlando Pereira, Universidade do Minho
# 
# jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
# 
# $Id: Makefile,v 1.1 2005/02/24 05:24:07 philgrim Exp $

TOPDIR  := $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)/../../..

# Edit this file to set the compiler/ compiler options and send
# the modified file to jop@di.uminho.pt
include ../../Makefile.common

all: tests otests

alltests.h: alltests.x
	rpcgen -h alltests.x > alltests.h

alltests_xdr.c: alltests.x
	rpcgen -c alltests.x > alltests_xdr.c

%.o: %.c alltests.h
	$(CC) $(CCFLAGSG) -c -o $@ $<

o%.o: %.c alltests.h
	$(CC) $(CCFLAGSO) -c -o $@ $<

tests: alltests_xdr.o tests.o
	$(CC) $(CCFLAGSG) -o tests tests.o alltests_xdr.o

otests: oalltests_xdr.o otests.o
	$(CC) $(CCFLAGSO) -O16 -o otests otests.o oalltests_xdr.o

times: all
	echo "\nbench/rpcgen\n" >> ../xtl.times 2>&1
	echo "rpcgen" >> ../xtl.times 2>&1
	time tests >> ../xtl.times 2>&1
	time tests >> ../xtl.times 2>&1
	time tests >> ../xtl.times 2>&1
	echo "rpcgen opt" >> ../xtl.times 2>&1
	time otests >> ../xtl.times 2>&1
	time otests >> ../xtl.times 2>&1
	time otests >> ../xtl.times 2>&1

clean:
	rm -f *.o otests tests alltests_xdr.c alltests.h
