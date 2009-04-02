/*
 * Big Endian Network Byte Order encoding class for XTL.
 *
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
 */

#ifndef __XTL_BENBO
#define __XTL_BENBO

#include "config.h"

// Template policy to handle different sized simple types.  Works seemlessly on
// 32 and 64 bit platforms.
template< unsigned char >
class simple_type_policy;

template<>
class simple_type_policy< 1 >
{
public:
  static inline void copy(char const* in, char* out)
  {
    *out = *in;
  }
};

template<>
class simple_type_policy< 2 >
{
public:
  static inline void copy(char const* in, char* out)
  {
    _xtl_big_end_16( in, out );
  }
};

template<>
class simple_type_policy< 4 >
{
public:
  static inline void copy(char const* in, char* out)
  {
    _xtl_big_end_32( in, out );
  }
};

template<>
class simple_type_policy< 8 >
{
public:
  static inline void copy(char const* in, char* out)
  {
    _xtl_big_end_64( in, out );
  }
};


// Macros to keep things neat and tidy in class BENBO_format.
#define def_input_simple(type) \
	void input_simple(type& data) \
        { \
          simple_type_policy< sizeof( type ) >::copy( \
            reinterpret_cast<char const*>( this->require( sizeof( type ) ) ), \
            reinterpret_cast<char*>(&data) ); \
	} 

#define def_output_simple(type) \
	void output_simple(type const& data) \
        { \
          simple_type_policy< sizeof( type ) >::copy( \
            reinterpret_cast<char const*>(&data), \
            reinterpret_cast<char*>(this->desire( sizeof( type ) ) ) ); \
	} 


// BENBO_format class
template <class Buffer>
class BENBO_format: public generic_format<Buffer> {
 private:
 public:
	typedef Buffer buffer;

	BENBO_format(Buffer& buf):generic_format<Buffer>(buf) {}
	
	template <class Idx>
	void input_start_array(Idx& n) {input_simple(n);}
	template <class Idx>
	bool input_end_array(Idx& n) {return n--<=0;}

        // BENBO uses null terminated strings.  Find length.
	template <class Idx>
	void input_start_string(Idx& n) 
        {
          n = 0;
          //Look for null terminator.  Do NOT include terminator in count.
          while ( *(reinterpret_cast< char* >( this->require( 1 ) ) ) != '\0' )
          {
            ++n;
          }

          // Remember we read 1 more character than counted
          this->unrequire( n + 1 );
        }

	template <class Idx>
	bool input_end_string(Idx& n) 
        {
          // The null terminator has not been read.  There may be other
          // characters as well given max_len may have been used.  Advance past
          // the terminator.
          while ( *(reinterpret_cast< char* >( this->require( 1 ) ) ) != '\0' );
        }

	def_input_simple(bool)
	def_input_simple(char)
	def_input_simple(unsigned char)
	def_input_simple(short)
	def_input_simple(unsigned short)
	def_input_simple(int)
	def_input_simple(unsigned int)
	def_input_simple(long)
	def_input_simple(unsigned long)
	def_input_simple(longlong)
	def_input_simple(unsignedlonglong)
	def_input_simple(float)
	def_input_simple(double)

	void input_chars(char* data, int size) {
		input_raw(data, size);
	}

	// This routine is identical to that in GIOP_format
	void input_raw(char* data, int size) {
		int i;
		for(i=0;i<(size>>8)-1;i++,data+=256)
			memcpy(data, this->require(256), 256);
		int res=size-(i<<8);
		memcpy(data, this->require(res), res);
		if (res%4!=0)
			this->require(4-res%4);
	}

	template <class Idx>
	void output_start_array(Idx n) {output_simple(n);}
	void output_end_array() {}

  
        // BENBO uses null terminated strings.  Do nothing.
	template <class Idx>
	void output_start_string(Idx n) {}
        // Add the NULL terminator
        void output_end_string() 
        {
          this->output_simple( char( '\0') );
        }

	def_output_simple(bool)
	def_output_simple(char)
	def_output_simple(unsigned char)
	def_output_simple(short)
	def_output_simple(unsigned short)
	def_output_simple(int)
	def_output_simple(unsigned int)
	def_output_simple(long)
	def_output_simple(unsigned long)
	def_output_simple(longlong)
	def_output_simple(unsignedlonglong)
	def_output_simple(float)
	def_output_simple(double)

	void output_chars(char const* data, int size) {
		output_raw(data, size);
	}

	// This routine is identical to that in GIOP_format
	void output_raw(char const* data, int size) {
		int i;
		for(i=0;i<(size>>8)-1;i++,data+=256)
			memcpy(this->desire(256), data, 256);
		int res=size-(i<<8);
		memcpy(this->desire(res), data, res);
		if (res%4!=0)
			memset(this->desire(4-res%4), 0, 4-res%4);
	}
};

#undef def_input_simple
#undef def_output_simple

#endif
