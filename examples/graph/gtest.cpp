/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: gtest.cpp,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


#include <iostream>

#include <xtl/objio.h>
#include <xtl/graphio.h>
#include <xtl/text.h>

class loop {
 private:
 	loop* next;
	int val;

 public:
 	loop(int v):val(v) {}

	void set_next(loop* n) {next=n;}

	template <class Stream>
	void composite(Stream& stream) {
		stream.reference(next);
		stream.simple(val);
	}
};

int main() {
	loop l1(10), l2(20), l3(30), l4(40);

	l1.set_next(&l2);
	l2.set_next(&l3);
	l3.set_next(&l4);
	l4.set_next(&l1);

	char buf[1000];
	mem_buffer mb(buf, 1000);
	text_format<mem_buffer> tf(mb);
	obj_output<text_format<mem_buffer>, graph_refs> os(tf);

	os.simple(l1);

	*(char*)mb.require(1)=0;
	std::cout << mb.data() << std::endl;
}
