/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: alltests.x,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */

struct bench_hyper {
	long l;
	long h;
};

struct numbers {
 	bool aBool;
	char aChar; unsigned char anUChar;
	char aShort; unsigned short anUShort;
	int anInt; unsigned int anUInt;
	long aLong; unsigned long anULong;
	bench_hyper aLongLong; bench_hyper anULongLong; 
	float aFloat;
	double aDouble;
};

struct strings {
 	string ptr<>;
	char sptr[100];
	string cpp<>; 
};

struct arrays {
 	int fixed[10];
	int variable<>;
};

struct pointers {
 	int* refint;
	int* optint;
};

struct templates {
  /* n/a, we use an int to generate the same amount of data */
  int value;
};

struct pair{
	int first;
	int second;
};

struct containers {
  int lint<>;
  pair mint<>;
};

union unions switch(int discr) {
 case 0:
	int ival;
 case 1:
	float fval;
 default:
 	void;
};

struct base {
 	int i;
};

struct derived {
	base bogus;
 	float b;
};

union _bogus_obj switch(int discr) {
 case 0:
 	base bval;
 case 1:
 	derived dval;
 default:
 	void;
};

struct objects {
 	_bogus_obj* bptr1;
 	_bogus_obj* bptr2;
};

struct _bytes {
 	opaque fixed[10];
	opaque variable<>;
};

struct all_tests {
 	numbers n;
	strings s;
	arrays a;
	pointers p;
	templates t;
	containers c;
	unions u;
	objects o;
	_bytes b;
};

