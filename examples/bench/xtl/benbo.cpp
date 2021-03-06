/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: benbo.cpp,v 1.3 2011/08/05 21:03:11 keithsnively Exp $
 */


#include <iostream>

#include <xtl.h>

#define IMPL_ALLTESTS
#include "../../alltests.h"

int main() {
	const int size_buf = 500*1000;
	char buf[size_buf];

	mem_buffer mb(buf, size_buf);
	BENBO_format<mem_buffer> xf(mb);
	obj_output<BENBO_format<mem_buffer> > os(xf);
	
	all_tests to;
	to.init();

	for(int j=0;j<1000;j++) {
		xf.reset_buffer();
		for(int i=0;i<1000;i++)
			os.simple(to);
	}

	std::cout << mb.size() << std::endl;
}

