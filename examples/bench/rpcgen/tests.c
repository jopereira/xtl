/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: tests.c,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */

#include <string.h>
#include "alltests.h"
#include <rpc/xdr.h>

void init_numbers(numbers* n) {
	n->aBool=1;
	n->aChar=-1; n->anUChar=2;
	n->aShort=-3; n->anUShort=4;
	n->anInt=-5; n->anUInt=6;
	n->aLong=-9; n->anULong=10;
	n->aLongLong.l=-11; n->anULongLong.l=12;
	n->aFloat=13.14;
	n->aDouble=15.16;
}

void init_strings(strings* s) {
	s->ptr=(char*)malloc(20);
	strcpy(s->ptr, "XTL Test String 1");
	strcpy(s->sptr, "XTL Test String 2");
	s->cpp=(char*)malloc(20);
	strcpy(s->cpp, "XTL Test String 3");
}

void init_arrays(arrays* a) {
	int i;
	for(i=0;i<10;i++)
		a->fixed[i]=i*2;

	a->variable.variable_val=malloc(sizeof(int)*(a->variable.variable_len=10));
	for(i=0;i<a->variable.variable_len;i++)
		a->variable.variable_val[i]=i*3;
}

void init_pointers(pointers* p) {
	p->refint=(int*)malloc(sizeof(int));
	*p->refint=1;
	p->optint=NULL;
}

void init_templates(templates* t) {
	t->value=10;
}

void init_containers(containers* a) {
	int i;
	a->lint.lint_val=malloc(sizeof(int)*(a->lint.lint_len=10));
	for(i=0;i<a->lint.lint_len;i++)
		a->lint.lint_val[i]=i*3;
	a->mint.mint_val=malloc(sizeof(struct pair)*(a->mint.mint_len=10));
	for(i=0;i<a->mint.mint_len;i++) {
		a->mint.mint_val[i].first=i;
		a->mint.mint_val[i].second=i*3;
	}
}

void init_unions(unions* u) {
	u->discr=1;
	u->unions_u.fval=1.1;
}

void init_base(_bogus_obj* b) {
	b->discr=0;
	b->_bogus_obj_u.bval.i=2;
}

void init_derived(_bogus_obj* d) {
	d->discr=1;
	d->_bogus_obj_u.dval.b=3;
}

void init_objects(objects* o) {
	o->bptr1=(_bogus_obj*)malloc(sizeof(_bogus_obj));
	init_base(o->bptr1);
	o->bptr2=(_bogus_obj*)malloc(sizeof(_bogus_obj));
	init_base(o->bptr2);
	init_derived(o->bptr2);
}

void init_bytes(_bytes* b) {
	int i;
	for(i=0;i<10;i++)
		b->fixed[i]=i*2;

	b->variable.variable_val=(char*)malloc(b->variable.variable_len=10);
	for(i=0;i<b->variable.variable_len;i++)
		b->variable.variable_val[i]=i*3;
}

void init_all_tests(all_tests* a) {
	init_numbers(&a->n); init_strings(&a->s);
	init_arrays(&a->a); init_pointers(&a->p);
	init_templates(&a->t); init_containers(&a->c);
	init_unions(&a->u); init_objects(&a->o); init_bytes(&a->b);
}

int main() {
	char buf[300*1000];
	int i, j;
	all_tests to;
	XDR xdrs;

	init_all_tests(&to);
	for(j=0;j<100;j++) {
		xdrmem_create(&xdrs, buf, 300*1000, XDR_ENCODE);
		for(i=0;i<1000;i++)
			xdr_all_tests(&xdrs, &to);
		xdr_destroy(&xdrs);
	}
	return 0;
}

