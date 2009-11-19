# XTL - the eXternalization Template Library (sample code)
# by Jose' Orlando Pereira, Universidade do Minho
# 
# jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
#
# $Id: Makefile,v 1.3 2009/11/19 20:36:48 keithsnively Exp $

TOPDIR  := $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)/../../..

# Edit this file to set the compiler/ compiler options and send
# the modified file to jop@di.uminho.pt
include ../../Makefile.common

all: raw oraw giop ogiop xdr oxdr benbo obenbo container ocontainer

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
	echo "benbo" >> ../xtl.times 2>&1
	time ./benbo >> ../xtl.times 2>&1
	time ./benbo >> ../xtl.times 2>&1
	time ./benbo >> ../xtl.times 2>&1
	echo "benbo opt" >> ../xtl.times 2>&1
	time ./obenbo >> ../xtl.times 2>&1
	time ./obenbo >> ../xtl.times 2>&1
	time ./obenbo >> ../xtl.times 2>&1
	echo "container" >> ../xtl.times 2>&1
	time ./container >> ../xtl.times 2>&1
	time ./container >> ../xtl.times 2>&1
	time ./container >> ../xtl.times 2>&1
	echo "container opt" >> ../xtl.times 2>&1
	time ./ocontainer >> ../xtl.times 2>&1
	time ./ocontainer >> ../xtl.times 2>&1
	time ./ocontainer >> ../xtl.times 2>&1
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
	rm -f raw oraw giop ogiop xdr oxdr benbo obenbo core .depend .depend.bak

ifeq (.depend,$(wildcard .depend))
include .depend
endif
