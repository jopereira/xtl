/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: rawfilei.cpp,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


#include <iostream>
#include <fstream>

#include <xtl/objio.h>
#include <xtl/iostrbuf.h>

#include "../alltests.h"

void input(char buf[], all_tests& ti) {
	std::ifstream fstr("test.raw");
	istream_buffer fbi(fstr);
	raw_format<istream_buffer> rfi(fbi);
	obj_input<raw_format<istream_buffer> > is(rfi);

	is.composite(ti);
}
