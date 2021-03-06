/*
 * Core externaliztion utilities
 *
 * Copyright (C) 1998-2000 Jose' Orlando Pereira, jop@di.uminho.pt
 */
/* XTL - eXternalization Template Library - http://gsd.di.uminho.pt/~jop/xtl
 * Copyright (C) 1998-2000 Jose' Orlando Pereira, Universidade do Minho
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA
 *
 * $Id: objio.h,v 1.10 2010/08/03 13:21:32 keithsnively Exp $
 */

#ifndef __XTL_OBJIO
#define __XTL_OBJIO

#include <xtl/config.h>

#include <typeinfo>
#include <stdexcept>
#include <string>

//
template <class Stream, class T>
inline void composite(Stream& stream, T& data) {
	data.composite(stream);
}

#ifdef XTL_CONFIG_SIMPLE_CONTAINERS

#include <utility>
#include <vector>
#include <list>
#include <map>

template <class Stream, class T1, class T2>
inline void composite(Stream& stream, std::pair<const T1,T2>& data) {
	stream.simple(const_cast<T1&>(data.first));
	stream.simple(data.second);
}

template <class Stream, class T1, class T2>
inline void composite(Stream& stream, std::pair<T1,T2>& data) {
	stream.simple(data.first);
	stream.simple(data.second);
}

template <class Stream, class T>
inline void composite(Stream& stream, std::list<T>& data) {
	stream.container(data);
}

template <class Stream, class T>
inline void composite(Stream& stream, std::vector<T>& data) {
	stream.container(data);
}

template <class Stream, class T1, class T2>
inline void composite(Stream& stream, std::map<T1, T2>& data) {
	stream.container(data);
}

#endif


template <class Buffer>
class generic_format {
private:
	Buffer& buffer;
protected:
	void* require(int n)	{return buffer.require(n);}
	void unrequire(int n)	{buffer.unrequire(n);}
	void* desire(int n)	{return buffer.desire(n);}
	void undesire(int n)	{buffer.undesire(n);}

	void read(char* data, int size)		{buffer.read(data, size);}
	void write(char const* data, int size)	{buffer.write(data, size);}
public:
 	generic_format(Buffer& buf):buffer(buf) {}

	void input_start() {}

	void input_start_composite() {}
	void input_end_composite() {}

	void input_start_vector() {}
	void input_end_vector() {}

	virtual void output_start() {}

	void output_start_composite() {}
	void output_end_composite() {}

	void output_start_vector() {}
	void output_end_vector() {}

	void reset_buffer() {
		buffer.rewind();
		output_start();
	}

        inline int size() const
        {
          return buffer.size();
        }
};

template <class Buffer>
class raw_format: public generic_format<Buffer> {
 public:
 	typedef Buffer buffer;

 	raw_format(Buffer& buf):generic_format<Buffer>(buf) {}
	
	template <class T>
	inline void input_simple(T& data)
		{data=*((T*)this->require(sizeof(T)));}

	template <class Idx>
	void input_start_array(Idx& n) {input_simple(n);}
	template <class Idx>
	bool input_end_array(Idx& n) {return !(n-->0);}

	template <class Idx>
	void input_start_string(Idx& n) {input_simple(n);}
	template <class Idx>
	void input_end_string(Idx& n) {}

	void input_chars(char* data, int size) {input_raw(data, size);}

	void input_raw(char* data, int size) {
		int i;
		for(i=0;i<(size>>8)-1;i++,data+=256)
			std::memcpy(data, this->require(256), 256);
		int res=size-(i<<8);
		std::memcpy(data, this->require(res), res);
	}

	template <class T>
	inline void output_simple(T const& data)
		{*((T*)this->desire(sizeof(T)))=data;}

	template <class Idx>
	void output_start_array(Idx n) {output_simple(n);}
	void output_end_array() {}

	template <class Idx>
	void output_start_string(Idx n) {output_simple(n);}
        void output_end_string() {}

	void output_chars(char const* data, int size) {output_raw(data, size);}

	void output_raw(char const* data, int size) {
		int i;
		for(i=0;i<(size>>8)-1;i++,data+=256)
			std::memcpy(this->desire(256), data, 256);
		int res=size-(i<<8);
		std::memcpy(this->desire(res), data, res);
	}
};

#ifdef XTL_CONFIG_CHOICE_MACROS
#include <xtl/macros.h>
#endif

#ifdef XTL_CONFIG_COMPOSITE_BUG
#define XTL_CONTENT(d) composite(d)
#else
#define XTL_CONTENT(d) simple(d)
#define array_s array
#define vector_s vector
#endif

class no_refs;

#define def_simple_input(type) \
	inline obj_input& simple(type& data) { \
		format.input_simple(data); \
		return *this; \
	}

template <class Format, class References=no_refs>
class obj_input {
 private:
	Format& format;
 	References refs;

 public:
 	obj_input(Format& buf):format(buf)
		{format.input_start();}

	def_simple_input(bool);
	def_simple_input(char);
	def_simple_input(unsigned char);
	def_simple_input(short);
	def_simple_input(unsigned short);
	def_simple_input(int);
	def_simple_input(unsigned int);
	def_simple_input(long);
	def_simple_input(unsigned long);
	def_simple_input(longlong);
	def_simple_input(unsignedlonglong);
	def_simple_input(float);
	def_simple_input(double);

	inline obj_input& cstring(char*& data) {
		int size;
		format.input_start_string(size);
		data=new char[size+1];
		format.input_chars(data, size);
		data[size]=0;
		format.input_end_string(size);
		return *this;
	}

	inline obj_input& cstring(char* data, int max) {
		int size;
		format.input_start_string(size);

                if( size > max )
                {
                  // Handle the case where someone has written more bytes than
                  // we are reading.  This allows it to be more forgiving.
                  // Using the stack buffer saves about 20% - 40% in decoding
                  // time.
                  char s_buf[1024];
                  char * tmp = s_buf;
                  bool allocated = false;

                  if ( size > 1024 )
                  {
                    tmp = new char[size];
                    allocated = true;
                  }
                  format.input_chars(tmp, size);
                  memcpy( data, tmp, max );
                  if ( allocated ) delete[] tmp;
                }
                else
                {
                  format.input_chars(data, size);
                }
		data[size>max?max:size]=0;
		format.input_end_string(size);
		return *this;
	}

	inline obj_input& simple(std::string& data) {

		// Using the stack buffer saves about 20% - 40% in decoding time.
	        char s_buf[1024];
        	char * tmp = s_buf;
	        bool allocated = false;

		int size;
		format.input_start_string(size);
	        if ( size > 1024 )
        	{
        		tmp = new char[size];
	        	allocated = true;
	        }
		format.input_chars(tmp, size);
	        data.clear();
		data.append(tmp, size);
		format.input_end_string(size);

	        if ( allocated ) delete[] tmp;
		return *this;
	}

	template <class T>
	inline obj_input& vector(T data[], int size) {
		format.input_start_vector();
		for(int i=0;i<size;i++)
			XTL_CONTENT(data[i]);
		format.input_end_vector();
		return *this;
	}

	template <class T, class Idx>
	inline obj_input& array(T*& data, Idx& size) {
		format.input_start_array(size);
		data=new T[size];
		for(int j=size,i=0;!format.input_end_array(j);i++)
			XTL_CONTENT(data[i]);
		return *this;
	}

#ifdef XTL_CONFIG_COMPOSITE_BUG
	template <class T>
	inline obj_input& vector_s(T data[], int size) {
		format.input_start_vector();
		for(int i=0;i<size;i++)
			simple(data[i]);
		format.input_end_vector();
		return *this;
	}

	template <class T, class Idx>
	inline obj_input& array_s(T*& data, Idx& size) {
		format.input_start_array(size);
		data=new T[size];
		for(int j=size,i=0;!format.input_end_array(j);i++)
			simple(data[i]);
		return *this;
	}
#endif

	inline obj_input& opaque(char data[], int size) {
		format.input_start_vector();
		format.input_raw(data, size);
		format.input_end_vector();
		return *this;
	}

	template <class Idx>
	inline obj_input& bytes(char*& data, Idx& size) {
		int s=size;
		format.input_start_array(size);
		data=new char[size];
		format.input_raw(data, size);
		format.input_end_array(s);
		return *this;
	}

	// This is for compilers which do not support specialization
	// If possible, use simple(T&) below.
	template <class T>
	inline obj_input& composite(T& data) {
		format.input_start_composite();
		::composite(*this, data);
		format.input_end_composite();
		return *this;
	}

#ifndef XTL_CONFIG_COMPOSITE_BUG
	template <class T>
	inline obj_input& simple(T& data) {
		format.input_start_composite();
		::composite(*this, data);
		format.input_end_composite();
		return *this;
	}
#endif	

	template <class T>
	inline obj_input& reference(T*& data) {
		refs.reference(*this, data);
		return *this;
	}

	template <class T>
	inline obj_input& pointer(T*& data) {
		bool exists;
		simple(exists);
		if (exists) 
			reference(data);
		return *this;
	}

	template <class T>
        inline obj_input& container(std::vector< T > & data) {
                typedef std::vector< T > t_V;

                int j=0;
                format.input_start_array(j);

                // Do not preallocate array.  This allows for graceful failure on currupted input.
                t_V tmp;
                T etmp;

                if( j <= 1024 ) tmp.reserve( j );

                while(!format.input_end_array(j)) 
                {
                  tmp.push_back( etmp );
                  XTL_CONTENT( tmp.back() );
                }
                data.swap(tmp);
                return *this;
        }

        // std::vector< bool > is a special case according to the 1998 C++
        // specification since it is really a bitset and not a real vector.
        // Needs different handling here.
        inline obj_input& container(std::vector< bool > & data) {
                typedef std::vector< bool > t_V;

                int j=0;
                format.input_start_array(j);

                // Do not preallocate array.  This allows for graceful failure on currupted input.
                t_V tmp;
                bool b;

                if( j <= 1024 ) tmp.reserve( j );

                while(!format.input_end_array(j)) 
                {
                  XTL_CONTENT( b );
                  tmp.push_back( b );
                }

                data.swap(tmp);
                return *this;
        }

	template <class T>
        inline obj_input& container(std::list< T > & data) {
                typedef std::list< T > t_L;

                int j=0;
                format.input_start_array(j);
                
                // Do not preallocate array.  This allows for graceful failure on currupted input.
                t_L tmp;
                T etmp;

                while(!format.input_end_array(j)) 
                {
                  tmp.push_back( etmp );
                  XTL_CONTENT( tmp.back() );
                }
                data.swap(tmp);
                return *this;
        }

	template <class T>
        inline obj_input& container(T& data) {
                int j=0;
                T tmp;
                format.input_start_array(j);
                while(!format.input_end_array(j)) {
                        typename T::value_type v;
                        XTL_CONTENT(v);
                        tmp.insert(tmp.end(), v);
                }
                data.swap(tmp);
                return *this;
        }


#ifdef XTL_CONFIG_CHOICE_MACROS
	decl_ich_method(2)
	decl_ich_method(3)
	decl_ich_method(4)
	decl_ich_method(5)

	decl_iobj_method(2)
	decl_iobj_method(3)
	decl_iobj_method(4)
	decl_iobj_method(5)
#endif

        // Align on a boundary of size n
	inline obj_input& align(int n) {
          format.input_align( n );
          return *this;
	}
};

#define def_simple_output(type) \
	inline obj_output& simple(type const& data) { \
		format.output_simple(data); \
		return *this; \
	}

template <class Format, class References=no_refs>
class obj_output {
 private:
 	Format& format;
 	References refs;

 public:
 	obj_output(Format& buf):format(buf)
		{format.output_start();}

	def_simple_output(bool);
	def_simple_output(char);
	def_simple_output(unsigned char);
	def_simple_output(short);
	def_simple_output(unsigned short);
	def_simple_output(int);
	def_simple_output(unsigned int);
	def_simple_output(long);
	def_simple_output(unsigned long);
	def_simple_output(longlong);
	def_simple_output(unsignedlonglong);
	def_simple_output(float);
	def_simple_output(double);

	inline obj_output& cstring(char const* data) {
		int size=std::strlen(data);
		format.output_start_string(size);
		format.output_chars(data, size);
		format.output_end_string();
		return *this;
	}

	inline obj_output& cstring(char const* data, int max) {
                int size=std::strlen(data);
                format.output_start_string(size>max?max:size);
                format.output_chars(data, size>max?max:size);
                format.output_end_string();
                return *this;
	}

	inline obj_output& simple(const std::string& data) {
		int size=data.size();
		format.output_start_string(size);
		format.output_chars(data.data(), size);
		format.output_end_string();
		return *this;
	}

	template <class T>
	inline obj_output& vector(const T data[], int size) {
		format.output_start_vector();
		for(int i=0;i<size;i++)
			XTL_CONTENT(data[i]);
		format.output_end_vector();
		return *this;
	}

	template <class T, class Idx>
	inline obj_output& array(T const* data, Idx size) {
		format.output_start_array(size);
		for(int i=0;i<size;i++)
			XTL_CONTENT(data[i]);
		format.output_end_array();
		return *this;
	}
#ifdef XTL_CONFIG_COMPOSITE_BUG
	template <class T>
	inline obj_output& vector_s(const T data[], int size) {
		format.output_start_vector();
		for(int i=0;i<size;i++)
			simple(data[i]);
		format.output_end_vector();
		return *this;
	}

	template <class T, class Idx>
	inline obj_output& array_s(T const* data, Idx size) {
		format.output_start_array(size);
		for(int i=0;i<size;i++)
			simple(data[i]);
		format.output_end_array();
		return *this;
	}
#endif

	inline obj_output& opaque(const char data[], int size) {
		format.output_start_vector();
		format.output_raw(data, size);
		format.output_end_vector();
		return *this;
	}

	template <class Idx>
	inline obj_output& bytes(char const* data, Idx size) {
		format.output_start_array(size);
		format.output_raw(data, size);
		format.output_end_array();
		return *this;
	}

	// This is for compilers which do not support specialization
	// If possible, use simple(T&) below.
	template <class T>
	inline obj_output& composite(T const& data) {
		format.output_start_composite();
		::composite(*this, const_cast<T&>(data));
		format.output_end_composite();
		return *this;
	}

#ifndef XTL_CONFIG_COMPOSITE_BUG
	template <class T>
	inline obj_output& simple(T const& data) {
		format.output_start_composite();
		::composite(*this, const_cast<T&>(data));
		format.output_end_composite();
		return *this;
	}
#endif

	template <class T>
	inline obj_output& reference(T const* data) {
		refs.reference(*this, data);
		return *this;
	}

	template <class T>
	inline obj_output& pointer(T const* data) {
		bool exists=data!=NULL;
		simple(exists);
		if (exists)
			reference(data);
		return *this;
	}

	template <class T>
	inline obj_output& container(T const& data) {
		int j=data.size();
		format.output_start_array(j);
		for( typename T::const_iterator i=data.begin();
                     i != data.end();
                     ++i )
                {
			XTL_CONTENT(*i);
                }
		format.output_end_array();
		return *this;
	}

#ifdef XTL_CONFIG_CHOICE_MACROS
	decl_och_method(2)
	decl_och_method(3)
	decl_och_method(4)
	decl_och_method(5)

	decl_oobj_method(2)
	decl_oobj_method(3)
	decl_oobj_method(4)
	decl_oobj_method(5)

#define option(t) (t*)NULL

#endif
        // Align on a boundary of size n
	inline obj_output& align(int n) {
          format.output_align( n );
          return *this;
	}
};

#undef def_simple_input
#undef def_simple_output

class no_refs {
 public:
 	template <class Format, class T>
	void reference(obj_input<Format>& stream, T*& data) {
		delete data;
		data=new T;
		stream.XTL_CONTENT(*data);
	}

 	template <class Format, class T>
	void reference(obj_output<Format>& stream, T const* data) {
		stream.XTL_CONTENT(*data);
	}
};

// mem_buffer

class mem_buffer {
 private:
 	char *buffer, *ptr, *lim;

 public:
	class buffer_overflow_error: public std::overflow_error {
	 public:
	 	int bytes_left;
		int bytes_needed;

		buffer_overflow_error(int left, int needed):
		std::overflow_error("XTL mem_buffer overflow"),
			bytes_left(left),bytes_needed(needed) {}
	};

 	mem_buffer(void *buf, int size):
		buffer((char*)buf),ptr((char*)buf),lim(((char*)buf)+size) {}

	inline void read(char* ptr, int size)
		{std::memcpy(ptr, this->require(size), size);}
	inline void write(char const* ptr, int size)
		{std::memcpy(this->desire(size), ptr, size);}

	inline void* require(int size) {
		char* aux=ptr;
		if ((ptr+=size)>lim)
			throw buffer_overflow_error(lim-aux,size);
		return aux;
	}
	inline void* desire(int size)
		{return this->require(size);}
	inline void flush()
		{}

	inline void unrequire(int n)
		{ptr-=n;}
	inline void undesire(int n)
		{unrequire(n);}
	inline void rewind()
		{ptr=buffer;}
	inline int size()
		{return ptr-buffer;}
	inline char* data()
		{return buffer;}

	template <class Format>
	inline void composite(obj_input<Format>& stream) {
		int size, idx;
		stream.array(buffer, size).simple(idx);
		ptr=buffer+idx;
		lim=buffer+size;
	}

	template <class Format>
	inline void composite(obj_output<Format>& stream) {
		stream.array(buffer, lim-buffer).simple((int)(ptr-buffer));
	}

};



#endif
