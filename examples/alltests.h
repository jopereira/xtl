/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: alltests.h,v 1.2 2005/04/14 15:28:36 keithsnively Exp $
 */


#ifndef __XTL_TESTS
#define __XTL_TESTS

#include <list>
#include <map>
#include <string>
#include <utility>

class numbers {
 private:
 	bool aBool;
	char aChar;  unsigned char anUChar;
	char aChar2; short aShort; unsigned short anUShort;
	char aChar3; int anInt; unsigned int anUInt;
	char aChar4; long aLong; unsigned long anULong;
	char aChar5; longlong aLongLong; unsignedlonglong anULongLong;
	char aChar6; float aFloat; double aDouble;

 public:
 	numbers():
		aBool(false), aChar(0), anUChar(0), aChar2(0), aShort(0),
		anUShort(0), aChar3(0), anInt(0), anUInt(0), aChar4(0),
		aLong(0), anULong(0), aChar5(0), aLongLong(0),
		anULongLong(0), aChar6(0), aFloat(0), aDouble(0) {}

	void init() {
 		aBool=true;
		aChar=-1;   anUChar=2;
		aChar2=-3;  aShort=-4; anUShort=5;
		aChar3=-6;  anInt=-7;  anUInt=8;
		aChar4=-9;  aLong=-10; anULong=11;
		aChar5=-12; aLongLong=-13; anULongLong=(unsignedlonglong(12345678ul) << 32) | 9012ul;
		aChar6=-15; aFloat=(float)13.14; aDouble=15.16;
	}

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.simple(aBool).simple(aChar).simple(anUChar)
			.simple(aChar2).simple(aShort).simple(anUShort)
			.simple(aChar3).simple(anInt).simple(anUInt)
			.simple(aChar4).simple(aLong).simple(anULong)
			.simple(aChar5).simple(aLongLong).simple(anULongLong)
			.simple(aChar6).simple(aFloat).simple(aDouble);
	}

	bool operator==(const numbers& other) const {
 		return aBool==other.aBool &&
			aChar==other.aChar && 
			anUChar==other.anUChar &&
			aChar2==other.aChar2 &&
			aShort==other.aShort &&
			anUShort==other.anUShort &&
			aChar3==other.aChar3 &&
			anInt==other.anInt &&
			anUInt==other.anUInt &&
			aChar4==other.aChar4 &&
			aLong==other.aLong &&
			anULong==other.anULong &&
			aChar5==other.aChar5 &&
			aLongLong==other.aLongLong &&
			anULongLong==other.anULongLong &&
			aChar6==other.aChar6 &&
			aFloat==other.aFloat &&
			aDouble==other.aDouble;
	}
};

class strings {
 private:
 	char* ptr;
	char sptr[100];
	std::string cpp;

 public:
 	strings(): ptr((char*)0) {}
 	~strings() {delete [] ptr;}

 	void init() {
		ptr=new char[20];std::strcpy(ptr, "XTL Test String 1");
		std::strcpy(sptr, "XTL Test String 2");
		cpp="XTL Teste String 3";
	}

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.cstring(ptr).cstring(sptr, 100).simple(cpp);
	}

	bool operator==(const strings& other) const {
		return !std::strcmp(ptr, other.ptr) &&
			!std::strcmp(sptr, other.sptr) &&
			cpp==other.cpp;
	}
};

class arrays {
 private:
 	int fixed[10];

	int* variable;
	int size;

 public:
 	arrays(): variable((int*)0),size(0) {}
	~arrays() {delete [] variable;}

	void init() {
		for(int i=0;i<10;i++)
			fixed[i]=i*2;

		variable=new int[size=10];
		for(int i=0;i<size;i++)
			variable[i]=i*3;
	}

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.vector(fixed, 10);
		stream.array(variable, size);
	}

	bool operator==(const arrays& other) const {
		for(int i=0;i<10;i++)
			if (fixed[i]!=other.fixed[i])
				return false;

		if (size!=other.size)
			return false;
		for(int i=0;i<size;i++)
			if (variable[i]!=other.variable[i])
				return false;

		return true;
	}
};

class pointers {
 private:
 	int* refint;
	int* optint;

 public:
 	pointers(): refint((int*)0), optint((int*)0) {}
	~pointers() {delete refint; delete optint;}

	void init() {
		refint=new int;
		*refint=1;
	}

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.reference(refint).pointer(optint);
	}

	bool operator==(const pointers& other) const {
		return *refint==*other.refint &&
			optint==other.optint;
	}
};

template <class T>
class templates {
 private:
 	T value;

 public:
 	templates(): value(0) {}
 	~templates() {}

	void init() {
		value=10;
	}

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.simple(value);
	}

	bool operator==(const templates& other) const {
		return value==other.value;
	}
};

class containers {
 private:
	std::list<int> lint;
	std::map<int,int> mint;

 public:
	void init() {
		for(int i=0;i<10;i++)
			lint.insert(lint.end(),i);
		for(int i=0;i<10;i++) 
			mint.insert(std::pair<int const,int>(i,i*2));
	}

	template <class Stream>
	inline void composite(Stream& stream) {
#ifdef XTL_CONFIG_SIMPLE_CONTAINERS
		stream.simple(lint).simple(mint);
#else
		stream.container(lint);
#endif
	}

	bool operator==(const containers& other) const {
		return true; //FIXME
	}
};

#ifdef XTL_CONFIG_CHOICE_MACROS
class unions {
 private:
	int discr;
	union {
		int ival;
		float fval;
	} val;

 public:
	unions(): discr(0) {val.ival=0;}

	void init() {
		discr=1;
		val.fval=1.1f;
	}

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.choices(discr, val.ival, val.fval);
	}

	bool operator==(const unions& other) const {
		return discr==other.discr &&
			(discr==0?val.ival==other.val.ival:val.fval==other.val.fval);
	}
};

class base {
 private:
 	int i;

 public:
 	base():i(0) {}
 	virtual ~base();

	virtual void init();

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.simple(i);
	}

	bool operator==(const base& other) const {
		return i==other.i;
	}
};

class derived: public base {
 private:
 	float b;

 public:
 	derived(): b(0) {}
	~derived();

	virtual void init();

	template <class Stream>
	inline void composite(Stream& stream) {
		base::composite(stream);
		stream.simple(b);
	}

	bool operator==(const derived& other) const {
		return base::operator==(other) && b==other.b;
	}
};

class objects {
 private:
 	base* bptr1;
 	base* bptr2;

 public:
 	objects(): bptr1((base*)0), bptr2((base*)0) {}
 	~objects() {delete bptr1; delete bptr2;}

	void init() {
		bptr1=new base;
		bptr1->init();
		bptr2=new derived;
		bptr2->init();
	}

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.object(bptr1, (base*)0, (derived*)0)
			.object(bptr2, (base*)0, (derived*)0);
	}

	bool operator==(const objects& other) const {
		return true;
		derived* oder;
		try {
			oder=dynamic_cast<derived*>(other.bptr2);
		} catch(...) {
			return false;
		}
		return *bptr1==*other.bptr1 && *bptr2==*oder;
	}
};
#endif

class bytes {
 private:
 	char fixed[10];

	char* variable;
	int size;

 public:
 	bytes(): variable((char*)0),size(0) {}
	~bytes() {delete [] variable;}

	void init() {
		for(int i=0;i<10;i++)
			fixed[i]=i*2+40;

		variable=new char[size=10];
		for(int i=0;i<size;i++)
			variable[i]=i*3+50;
	}

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.opaque(fixed, 10).bytes(variable, size);
	}

	bool operator==(const bytes& other) const {
		for(int i=0;i<10;i++)
			if (fixed[i]!=other.fixed[i])
				return false;

		if (size!=other.size)
			return false;
		for(int i=0;i<size;i++)
			if (variable[i]!=other.variable[i])
				return false;

		return true;
	}
};

class all_tests {
 private:
 	numbers n;
	strings s;
	arrays a;
	pointers p;
	templates<int> t;
	containers c;
#ifdef XTL_CONFIG_CHOICE_MACROS
	unions u;
	objects o;
#endif
	bytes b;

 public:
 	void init() {
		n.init(); s.init(); a.init(); p.init(); t.init();
		c.init();
#ifdef XTL_CONFIG_CHOICE_MACROS
		u.init(); o.init();
#endif
		b.init();
	}

	template <class Stream>
	inline void composite(Stream& stream) {
		stream.simple(n);
		stream.simple(s);
		stream.simple(a);
		stream.simple(p);
		stream.simple(t);
		stream.simple(c);
#ifdef XTL_CONFIG_CHOICE_MACROS
		stream.simple(u);
		stream.simple(o);
#endif
		stream.simple(b);
	}

	bool operator==(const all_tests& other) const {
		return n==other.n &&
			s==other.s &&
			a==other.a &&
			p==other.p &&
			t==other.t &&
			c==other.c &&
#ifdef XTL_CONFIG_CHOICE_MACROS
			u==other.u &&
			o==other.o &&
#endif
			b==other.b &&
			true;
	}
};

#if defined(IMPL_ALLTESTS) && defined(XTL_CONFIG_CHOICE_MACROS)
base::~base() {}

void base::init() {
	i=2;
}

derived::~derived() {}

void derived::init() {
	base::init();
	b=3;
}
#endif

#endif
