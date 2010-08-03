/*
 * XDR format driver for XTL
 *
 * Copyright (C) 1998-2000 Jose' Orlando Pereira, jop@di.uminho.pt
 * Copyright (C) 2000 Angus Leeming, a.leeming@ic.ac.uk
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
 * $Id: xdr.h,v 1.9 2010/08/03 13:21:32 keithsnively Exp $
 */

#ifndef __XTL_XDR
#define __XTL_XDR

#include "config.h"

// Template policy to handle different sized simple types.  Works seemlessly on
// 32 and 64 bit platforms.
template< unsigned char >
class simple_xdr_policy;

// Only types of size 4 and 16 should be supported for XDR.  Everything else
// will fail to compile (a good thing).
template<>
class simple_xdr_policy< 4 >
{
public:
  static inline void copy(char const* in, char* out)
  {
    _xtl_big_end_32( in, out );
  }
};

template<>
class simple_xdr_policy< 8 >
{
public:
  static inline void copy(char const* in, char* out)
  {
    _xtl_big_end_64( in, out );
  }
};

// Macros to keep things neat and tidy in class XDR_format.
// All data is stored in 32 bit or 64 bit chunks (XDR standard RFC 1832)
#define def_input_simple_xdr_t(type1, type2) \
	void input_simple(type1& data) { \
		type2 store; \
		simple_xdr_policy< sizeof( type2 ) >::copy( \
                         reinterpret_cast<char const*>( this->require( sizeof( type2 ) ) ), \
			 reinterpret_cast<char*>( &store ) ); \
		data = static_cast<type1>( store ); \
	} 

#define def_output_simple_xdr_t(type1, type2) \
 	void output_simple(type1 const& data) { \
		type2 store = static_cast<type2>( data ); \
		simple_xdr_policy< sizeof( type2 ) >::copy( \
		         reinterpret_cast<char const*>( &store ), \
			 reinterpret_cast<char*>( this->desire( sizeof( type2 ) ) ) ); \
	}

// The following macros do not require a copy
#define def_input_simple_xdr(type) \
	void input_simple(type& data) \
        { \
          simple_xdr_policy< sizeof( type ) >::copy( \
            reinterpret_cast<char const*>( this->require( sizeof( type ) ) ), \
            reinterpret_cast<char*>(&data) ); \
	} 

#define def_output_simple_xdr(type) \
	void output_simple(type const& data) \
        { \
          simple_xdr_policy< sizeof( type ) >::copy( \
            reinterpret_cast<char const*>(&data), \
            reinterpret_cast<char*>(this->desire( sizeof( type ) ) ) ); \
	} 

template <class Buffer>
class XDR_format: public generic_format<Buffer> {
 private:
 public:
	typedef Buffer buffer;

	XDR_format(Buffer& buf):generic_format<Buffer>(buf) {}
	
	template <class Idx>
	void input_start_array(Idx& n) {input_simple(n);}
	template <class Idx>
	bool input_end_array(Idx& n) {return n--<=0;}

	template <class Idx>
	void input_start_string(Idx& n) {input_simple(n);}
	template <class Idx>
	void input_end_string(Idx& n) {}

	def_input_simple_xdr_t(bool, int)
	def_input_simple_xdr_t(char, int)
	def_input_simple_xdr_t(unsigned char, int)
	def_input_simple_xdr_t(short, int)
	def_input_simple_xdr_t(unsigned short, int)

        // These types do not need to be translated, avoiding a copy.  Note that
        // "long" is treated as native length.
	def_input_simple_xdr(int)
	def_input_simple_xdr(unsigned int)
	def_input_simple_xdr(long)
	def_input_simple_xdr(unsigned long)
	def_input_simple_xdr(longlong)
	def_input_simple_xdr(unsignedlonglong)
	def_input_simple_xdr(float)
	def_input_simple_xdr(double)

	void input_chars(char* data, int size) {
		input_raw(data, size);
	}

	// This routine is identical to that in GIOP_format
	void input_raw(char* data, int size) {
		int i;
		for(i=0;i<(size>>8)-1;i++,data+=256)
			std::memcpy(data, this->require(256), 256);
		int res=size-(i<<8);
		std::memcpy(data, this->require(res), res);
		if (res%4!=0)
			this->require(4-res%4);
	}

	template <class Idx>
	void output_start_array(Idx n) {output_simple(n);}
	void output_end_array() {}

	template <class Idx>
	void output_start_string(Idx n) {output_simple(n);}
        void output_end_string() {}

	def_output_simple_xdr_t(bool, int)
	def_output_simple_xdr_t(char, int)
	def_output_simple_xdr_t(unsigned char, int)
	def_output_simple_xdr_t(short, int)
	def_output_simple_xdr_t(unsigned short, int)

        // These types do not need to be translated, avoiding a copy.  Note that
        // "long" is treated as native length.
	def_output_simple_xdr(int)
	def_output_simple_xdr(unsigned int)
	def_output_simple_xdr(long)
	def_output_simple_xdr(unsigned long)
	def_output_simple_xdr(longlong)
	def_output_simple_xdr(unsignedlonglong)
	def_output_simple_xdr(float)
	def_output_simple_xdr(double)

	void output_chars(char const* data, int size) {
		output_raw(data, size);
	}

	// This routine is identical to that in GIOP_format
	void output_raw(char const* data, int size) {
		int i;
		for(i=0;i<(size>>8)-1;i++,data+=256)
			std::memcpy(this->desire(256), data, 256);
		int res=size-(i<<8);
		std::memcpy(this->desire(res), data, res);
		if (res%4!=0)
			std::memset(this->desire(4-res%4), 0, 4-res%4);
	}

        // These methods will only work if the buffer size may be queried.  It
        // would be too expensive to keep track of alignment, only to use here.
        // The work around would be to create a buffer wrapper that allows size
        // to be queried (or always returns 0).
        inline void input_align( int n )
        {
          if ( n % 4 ) n += 4 - ( n % 4);

          int align_incr = ((this->size() % n) ? (n - (this->size() % n)) : 0);

          this->require( align_incr );
        }

        inline void output_align( int n )
        {
          if ( n % 4 ) n += 4 - ( n % 4);

          int align_incr = ((this->size() % n) ? (n - (this->size() % n)) : 0);
          std::memset( this->desire( align_incr ), '\0', align_incr );
        }
};

#undef def_input_simple_xdr_t
#undef def_input_simple_xdr_t
#undef def_output_simple_xdr_t
#undef def_output_simple_xdr_t
#undef LOW
#undef HIGH

#endif
