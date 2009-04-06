/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: tests.cpp,v 1.2 2009/04/06 19:38:21 keithsnively Exp $
 */

#include <xtl/config.h>
#include <iostream>

int main() {
	char buf1[500*1000], *ptr;
	char buf2[500];

	for(int j=0;j<500*1000;j++) {
          buf1[j] = j % 128;
        }
        
	for(int j=0;j<10000;j++) {
		ptr=buf1;
		for(int i=0;i<1000;i++,ptr+=480)
			memcpy(ptr, buf2, 480);
	}

        std::cout << 480*1000 << std::endl;
	return 0;
}
