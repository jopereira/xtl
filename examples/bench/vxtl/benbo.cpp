/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: benbo.cpp,v 1.1 2009/04/06 19:38:21 keithsnively Exp $
 */


#include <iostream>

#include <xtl/objio.h>
#include <xtl/vobjio.h>
#include <xtl/benbo.h>

#define IMPL_ALLTESTS
#include "../../alltests.h"

int main() {
	const int size_buf = 500*1000;
	char buf[size_buf];

	mem_buffer mb(buf, size_buf);
	v_format* vf=new v_format_wrap<BENBO_format<mem_buffer> >(mb);
	obj_output<v_format> os(*vf);

	all_tests to;
	to.init();

	for(int j=0;j<100;j++) {
		(*vf).reset_buffer();
		for(int i=0;i<1000;i++)
			os.composite(to);
	}

	std::cout << mb.size() << std::endl;
}

