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

all: raw oraw giop ogiop xdr oxdr 

%: %.cpp
	$(CXX) $(CXXFLAGSG) -o $@ $(INCLUDE) $<

o%: %.cpp
	$(CXX) $(CXXFLAGSO) -o $@ $(INCLUDE) $<

times: all
	echo "\nbench/xtl\n" >> ../xtl.times 2>&1
	echo "xdr" >> ../xtl.times 2>&1
	time ./xdr >> ../xtl.times 2>&1
	time ./xdr >> ../xtl.times 2>&1
	time ./xdr >> ../xtl.times 2>&1
	echo "xdr opt" >> ../xtl.times 2>&1
	time ./oxdr >> ../xtl.times 2>&1
	time ./oxdr >> ../xtl.times 2>&1
	time ./oxdr >> ../xtl.times 2>&1
	echo "giop" >> ../xtl.times 2>&1
	time ./giop >> ../xtl.times 2>&1
	time ./giop >> ../xtl.times 2>&1
	time ./giop >> ../xtl.times 2>&1
	echo "giop opt" >> ../xtl.times 2>&1
	time ./ogiop >> ../xtl.times 2>&1
	time ./ogiop >> ../xtl.times 2>&1
	time ./ogiop >> ../xtl.times 2>&1
	echo "raw" >> ../xtl.times 2>&1
	time ./raw >> ../xtl.times 2>&1
	time ./raw >> ../xtl.times 2>&1
	time ./raw >> ../xtl.times 2>&1
	echo "raw opt" >> ../xtl.times 2>&1
	time ./oraw >> ../xtl.times 2>&1
	time ./oraw >> ../xtl.times 2>&1
	time ./oraw >> ../xtl.times 2>&1

dep:
	touch .depend
	makedepend -f .depend $(INCLUDE) *.cpp

clean:
	rm -f raw oraw giop ogiop xdr oxdr core .depend .depend.bak

ifeq (.depend,$(wildcard .depend))
include .depend
endif
