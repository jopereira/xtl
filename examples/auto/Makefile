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

all: auto

auto: auto.cpp  $(XTL)
	$(CXX) $(CXXFLAGS) -o auto $(INCLUDE) auto.cpp

dep:
	makedepend -f .depend $(INCLUDE) *.cpp

clean:
	rm -f *.o auto core .depend .depend.bak

ifeq (.depend,$(wildcard .depend))
include .depend
endif
