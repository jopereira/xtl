/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: main.cpp,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


#include <iostream>

#include <xtl/objio.h>
#include <xtl/text.h>

#define IMPL_ALLTESTS
#include "../alltests.h"

void input(char buf[], all_tests& ti);
void output(char buf[], const all_tests& to);
void compare(const all_tests& to, const all_tests& ti);

int main(int argc, char* argv[]) {
	char buf[4000];

	std::cout << "Testing " << argv[0] << ": ";
	std::cout.flush();

	all_tests to;
	to.init();
	output(buf, to);

	all_tests ti;
	input(buf, ti);

	compare(to, ti);

	// uncomment when debugging
#if 0
	mem_buffer xmbo(buf, 4000);
	text_format<mem_buffer> xrfo(xmbo);
	obj_output<text_format<mem_buffer> > xos(xrfo);
	xos.simple(to);
	buf[xmbo.size()]=0;
	std::cout << buf << std::endl;
	xmbo.rewind();
	xos.simple(ti);
	buf[xmbo.size()]=0;
	std::cout << buf << std::endl;
#endif
	return 0;
}
