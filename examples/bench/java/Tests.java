/*
 * XTL - the eXternalization Template Library (sample code)
 * by Jose' Orlando Pereira, Universidade do Minho
 *
 * jop@di.uminho.pt - http://gsd.di.uminho.pt/~jop
 *
 * $Id: Tests.java,v 1.1 2005/02/24 05:24:07 philgrim Exp $
 */


import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;
import java.util.Date;

public class Tests {
	public static void main(String args[]) {
		try {
		Date start, end;
		ByteArrayOutputStream baos=new ByteArrayOutputStream();
		Alltests t=new Alltests();
		t.init();

		start=new Date();
		for(int i=0;i<1000;i++) {
			ObjectOutputStream oos=new ObjectOutputStream(baos);
			oos.writeObject(t);
		}
		end=new Date();
		float elaps=(float)(end.getTime()-start.getTime())/1000;
		System.out.println("Avg time: "+elaps+"ms "+baos.size()+" bytes");
		} catch(Exception e) {
			System.out.println("E: "+e);
		}
	}
};

