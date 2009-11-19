/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: container.cpp,v 1.1 2009/11/19 20:36:48 keithsnively Exp $
 */


#include <iostream>

#include <xtl.h>

#define IMPL_ALLTESTS
#include "../../alltests.h"

#define CONTAINER_SIZE 100
#define ITERATIONS 1000

int main() {
       // Allocate enough room for 100 copies of container
	const unsigned int size_buf = 100*4*5*CONTAINER_SIZE;
	char* buf = new char[size_buf];

        //all_tests to;
        containers_t< CONTAINER_SIZE > to;
        containers_t< CONTAINER_SIZE > from;
        to.init();

        {
          mem_buffer mb(buf, size_buf);
          BENBO_format<mem_buffer> xf(mb);
          obj_output<BENBO_format<mem_buffer> > os(xf);

          mem_buffer imb(buf, size_buf);
          BENBO_format<mem_buffer> ixf(imb);
          obj_input<BENBO_format<mem_buffer> > is(ixf);
	
          for(int j=0;j<ITERATIONS;j++) {
            xf.reset_buffer();
            ixf.reset_buffer();
            for(int i=0;i<100;i++)
            {
              os.simple(to);
            }
            for(int i=0;i<100;i++)
            {
              is.simple(from);
            }
          }

          std::cout << mb.size() << std::endl;
        }


        {
          mem_buffer mb(buf, size_buf);
          XDR_format<mem_buffer> xf(mb);
          obj_output<XDR_format<mem_buffer> > os(xf);

          mem_buffer imb(buf, size_buf);
          XDR_format<mem_buffer> ixf(imb);
          obj_input<XDR_format<mem_buffer> > is(ixf);
	
          for(int j=0;j<ITERATIONS;j++) {
            xf.reset_buffer();
            ixf.reset_buffer();
            for(int i=0;i<100;i++)
            {
              os.simple(to);
            }
            for(int i=0;i<100;i++)
            {
              is.simple(from);
            }
          }

          std::cout << mb.size() << std::endl;
        }
        
        delete[] buf;
}

