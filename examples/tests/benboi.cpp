/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: benboi.cpp,v 1.1 2006/08/29 18:42:37 keithsnively Exp $
 */


#include <iostream>

#include <xtl/objio.h>
#include <xtl/benbo.h>

#include "../alltests.h"

void input(char buf[], all_tests& ti) {
	mem_buffer mbi(buf, 1000);
	BENBO_format<mem_buffer> rfi(mbi);
	obj_input<BENBO_format<mem_buffer> > is(rfi);

	is.composite(ti);
}
