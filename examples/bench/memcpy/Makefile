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

tests: tests.cpp
	$(CXX) $(CXXFLAGSG) -o $@ $(INCLUDE) $<

otests: tests.cpp 
	$(CXX) $(CXXFLAGSO) -o $@ $(INCLUDE) $<

times: all
	echo "\nbench/memcpy\n" >> ../xtl.times 2>&1
	echo "memcpy" >> ../xtl.times 2>&1
	time tests >> ../xtl.times 2>&1
	time tests >> ../xtl.times 2>&1
	time tests >> ../xtl.times 2>&1
	echo "memcpy opt" >> ../xtl.times 2>&1
	time otests >> ../xtl.times 2>&1
	time otests >> ../xtl.times 2>&1
	time otests >> ../xtl.times 2>&1

clean:
	rm -f tests otests
