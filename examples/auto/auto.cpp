/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: auto.cpp,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


#include <iostream>

#include <xtl/autoio.h>
#include <xtl/xdr.h>

class obj: public externalizable_base {
 private:
 	decl_externalizable(obj);

 	int a, b;
 	
 public:
 	template <class Stream>
	void composite(Stream& stream) {
		stream.simple(a).simple(b);
	}

	virtual void hello() {
		std::cout << "Sou um obj" << std::endl;
	}
};

class deriv_obj: public obj {
 private:
 	decl_externalizable(deriv_obj);

 	int c, d;
 	
 public:
 	template <class Stream>
	void composite(Stream& stream) {
		obj::composite(stream);
		stream.simple(c).simple(d);
	}

	virtual void hello() {
		std::cout << "Sou um deriv_obj" << std::endl;
	}
};

class other: public obj {
 private:
 	decl_externalizable(other);

 	int a;
 	
 public:
 	template <class Stream>
	void composite(Stream& stream) {
		obj::composite(stream);
		stream.simple(a);
	}

	virtual void hello() {
		std::cout << "Sou um other" << std::endl;
	}
};

externalizable_index idx;
impl_externalizable(obj, 69, idx);
impl_externalizable(deriv_obj, 105, idx);
impl_externalizable(other, 45, idx);

int main() {
	char buf[1000];
	mem_buffer mb(buf, 1000);
	v_format_wrap<XDR_format<mem_buffer> > tf(mb);
	auto_obj_output os(tf);

	obj* t1=new obj;
	obj* t2=new deriv_obj;
	obj* t3=new other;

	t1->hello();
	t2->hello();
	t3->hello();

	os.auto_object(t1);
	os.auto_object(t2);
	os.auto_object(t3);

	delete t1; delete t2; delete t3;
	t1=t2=t3=NULL;

	std::cout << mb.size() << std::endl;

	mem_buffer mb2(buf, mb.size());
	v_format_wrap<XDR_format<mem_buffer> > tf2(mb2);
	auto_obj_input is(tf2, idx);

	is.auto_object(t1);
	is.auto_object(t2);
	is.auto_object(t3);

	t1->hello();
	t2->hello();
	t3->hello();
}

