/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: rawfileo.cpp,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */

#include <iostream>
#include <fstream>

#include <xtl/objio.h>
#include <xtl/iostrbuf.h>

#include "../alltests.h"

void output(char buf[], const all_tests& to) {
	std::ofstream fstr("test.raw");
	ostream_buffer fbo(fstr);
	raw_format<ostream_buffer> rfo(fbo);
	obj_output<raw_format<ostream_buffer> > os(rfo);

	os.composite(to);
}
