/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: main.cpp,v 1.6 2009/04/06 19:38:21 keithsnively Exp $
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
  try
  {
	char buf[4000];

	std::cout << "Testing " << argv[0] << ": ";
	std::cout.flush();

	all_tests to;
	to.init();
        std::cout << "Writing.." << std::endl;
	output(buf, to);

	all_tests ti;
        std::cout << "Reading.." << std::endl;
	input(buf, ti);

        std::cout << "Comparing.." << std::endl;
	compare(to, ti);

        std::cout << to << std::endl;
        std::cout << ti << std::endl;
	// uncomment when debugging
#if 1
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
  }
  catch( mem_buffer::buffer_overflow_error const & ex )
  {
    std::cerr << "Caught mem_buffer::buffer_overflow_error: " 
              << ex.what() 
              << ", bytes left: " << ex.bytes_left
              << ", bytes needed: " << ex.bytes_needed
              << std::endl;
    return 1;
  }
  catch( std::exception const & ex )
  {
    std::cerr << "Caught std::exception: " << ex.what() << std::endl;
    return 1;
  }

  return 0;
}
