/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: raw.cpp,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


#include <iostream>

#include <xtl/objio.h>

#define IMPL_ALLTESTS
#include "../../alltests.h"

int main() {
	const int size_buf = 500*1000;
	char buf[size_buf];

	mem_buffer mb(buf, size_buf);
	raw_format<mem_buffer> rf(mb);
	obj_output<raw_format<mem_buffer> > os(rf);

	all_tests to;
	to.init();

	for(int j=0;j<100;j++) {
		rf.reset_buffer();
		for(int i=0;i<1000;i++)
			os.simple(to);
	}

	std::cout << mb.size() << std::endl;
}

