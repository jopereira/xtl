/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: rawo.cpp,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


#include <iostream>

#include <xtl/objio.h>

#include "../alltests.h"

void output(char buf[], const all_tests& to) {
	mem_buffer mbo(buf, 1000);
	raw_format<mem_buffer> rfo(mbo);
	obj_output<raw_format<mem_buffer> > os(rfo);

	os.composite(to);
}
