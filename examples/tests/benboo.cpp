/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: benboo.cpp,v 1.1 2006/08/29 18:42:37 keithsnively Exp $
 */


#include <iostream>

#include <xtl/objio.h>
#include <xtl/benbo.h>

#include "../alltests.h"

void output(char buf[], const all_tests& to) {
	mem_buffer mbo(buf, 1000);
	BENBO_format<mem_buffer> rfo(mbo);
	obj_output<BENBO_format<mem_buffer> > os(rfo);

	os.composite(to);
}
