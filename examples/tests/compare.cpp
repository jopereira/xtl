/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: compare.cpp,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


#include <iostream>
#include <xtl/objio.h>

#include "../alltests.h"

void compare(const all_tests& to, const all_tests& ti) {
	std::cout << (to==ti?"PASSED":"Failed") << std::endl;
}

