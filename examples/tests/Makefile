# XTL - the eXternalization Template Library (sample code)
# by Jose' Orlando Pereira, Universidade do Minho
# 
# jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
#
# $Id: Makefile,v 1.1 2005/02/24 05:24:07 philgrim Exp $

TOPDIR  := $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)/../..

# Edit this file to set the compiler/ compiler options and send
# the modified file to jop@di.uminho.pt
include ../Makefile.common

all: nonopt opt

nonopt: raw giop xdr rawfile

opt: oraw ogiop oxdr

%.o: %.cpp
	$(CXX) $(CXXFLAGSG) -c -o $@ $(INCLUDE) $<

%: main.o %i.o %o.o compare.o
	$(CXX) $(LDFLAGS) -o $@ main.o $@i.o $@o.o compare.o

o%.o: %.cpp
	$(CXX) $(CXXFLAGSO) -c -o $@ $(INCLUDE) $<

o%: main.o o%i.o o%o.o compare.o
	$(CXX) $(LDFLAGS) -o $@ main.o $@i.o $@o.o compare.o

tests: xtl.tests
	cat xtl.tests

xtl.tests: all
	(./raw ; ./oraw ; ./giop ; ./ogiop ; ./xdr ; ./oxdr) > xtl.tests 2>&1

dep:
	touch .depend
	makedepend -f .depend $(INCLUDE) *.cpp

clean:
	rm -f raw oraw giop ogiop xdr oxdr rawfile *.o test.raw xtl.tests core .depend .depend.bak

ifeq (.depend,$(wildcard .depend))
include .depend
endif
