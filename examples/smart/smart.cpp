/*
 * XTL - the eXternalization Template Library (sample code)
 * by 1998 Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: smart.cpp,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


#include <iostream>

#include <xtl/objio.h>
#include <xtl/graphio.h>
#include <xtl/text.h>

class C {
 private:
 	int refcnt;
	int data;
 public:
 	C(int v):refcnt(0),data(v) {}

	void incref()
		{refcnt++;}
	int decref()
		{return --refcnt;}

	template <class Stream>
	void composite(Stream& stream) {
		stream.simple(data);
	}
};

class R {
 private:
 	C* ptr;
 public:
 	R():ptr((C*)0) {}
 	R(C* p):ptr(p)
		{if (ptr) ptr->incref();}
 	R(R& p):ptr(p.ptr)
		{if (ptr) ptr->incref();}
	~R()
		{if (ptr && !ptr->decref()) delete ptr;}

	C& operator*()		{return *ptr;}

	template <class Format, class Refs>
	void composite(obj_input<Format,Refs>& stream) {
		if (ptr && !ptr->decref()) delete ptr;
		ptr=(C*)0;
		stream.pointer(ptr);
		if (ptr) ptr->incref();
	}

	template <class Format, class Refs>
	void composite(obj_output<Format,Refs>& stream) {
		stream.pointer(ptr);
	}
};

class T {
	R r1,r2;
 public:
 	T() {}
 	T(int v):r1(new C(v)),r2(r1) {}

	template <class Stream>
	void composite(Stream& stream) {
		stream.simple(r1).simple(r2);
	}
};

int main() {
	char buf[1000];
	mem_buffer mb(buf, 1000);
	text_format<mem_buffer> tf(mb);
	obj_output<text_format<mem_buffer>, graph_refs> os(tf);

	T t(10);

	os.simple(t);

	*(char*)mb.require(1)=0;
	std::cout << mb.data() << std::endl;
}
