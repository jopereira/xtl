/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: Alltests.java,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


import java.io.Serializable;
import java.util.Vector;

class numbers implements Serializable {
 	boolean aBool;
	byte aChar; byte anUChar;
	char aShort; char anUShort;
	int anInt; int anUInt;
	int aLong; int anULong;
	long aLongLong; long anULongLong; 
	float aFloat;
	double aDouble;
};

class strings implements Serializable {
 	private String ptr="XTL Test String 1";
	private String sptr="XTL Test String 2";
	private String cpp="XTL Test String 3";
};

class arrays implements Serializable {
 	private int fixed[]=new int[10];
	private int variable[];

	public void init() {
		for(int i=0;i<10;i++)
			fixed[i]=i*2;

		variable=new int[10];
		for(int i=0;i<10;i++)
			fixed[i]=i*3;
	}
};

class pointers implements Serializable {
 	private Integer refint;
	private Integer optint=null;

	public void init() {
 		refint=new Integer(1);
	}
};

class templates implements Serializable {
	/* n/a, we use an int to generate the same amount of data */
	private int value=10;
};

class containers implements Serializable {
	Vector lint;

	public void init() {
		lint=new Vector();
		for(int i=0;i<10;i++)
			lint.addElement(new Integer(i));
	}
};

class unions implements Serializable {
	private Object val;
	
	public void init() {
		val=new Float(1.1);
	}
};

class base implements Serializable {
 	private int i=2;
};

class derived extends base implements Serializable {
 	private float b=3;
};

class objects implements Serializable {
 	base bptr1;
 	base bptr2;

	public void init() {
 		bptr1=new base();
 		bptr2=new derived();
	}
};

class bytes implements Serializable {
 	byte fixed[]=new byte[10];
	byte variable[];

	public void init() {
		for(int i=0;i<10;i++)
			fixed[i]=(byte)(i*2);

		variable=new byte[10];
		for(int i=0;i<10;i++)
			fixed[i]=(byte)(i*3);
	}
};

public class Alltests implements Serializable {
 	private numbers n;
	private strings s;
	private arrays a;
	private pointers p;
	private templates t;
	private containers c;
	private unions u;
	private objects o;
	private bytes b;

	public void init() {
 		n=new numbers();
		s=new strings();
		a=new arrays();
		a.init();
		p=new pointers();
		p.init();
		t=new templates();
		c=new containers();
		c.init();
		u=new unions();
		u.init();
		o=new objects();
		o.init();
		b=new bytes();
		b.init();
	}
};

