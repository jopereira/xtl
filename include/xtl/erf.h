/*
 * ERF style encoding class for XTL.
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

#ifndef __XTL_ERF
#define __XTL_ERF

#include "config.h"

template< class FORMAT >
class erf_buffer_access : public FORMAT
{
  typedef erf_buffer_access< FORMAT > This_t;

  erf_buffer_access();

public:
  static inline
  void* require( FORMAT& f, int n )	
  {
    return (( This_t& ) f ).FORMAT::require(n);
  }

  static inline
  void* desire( FORMAT& f, int n )	
  {
    return (( This_t& ) f ).FORMAT::desire(n);
  }
};

// Templates to input/output various sized data types.  Allows for easy addition
// of types, control over types supported and high level of optimization for
// each size.
template< class FORMAT, int N >
class erf_type_policy_impl
{
public:
  static void input( FORMAT & f, int & align, char * data )
  {
    *data = *( reinterpret_cast<char*>( erf_buffer_access< FORMAT >::require( f, N) ) );
    align += N;
  }

  static void output( FORMAT & f, int & align, char const * data )
  {
    *( reinterpret_cast<char*>( erf_buffer_access< FORMAT >::desire( f, N) ) ) = *data;
    align += N;
  }
};

template< class FORMAT, unsigned char >
class erf_type_policy
{};

template< class FORMAT >
class erf_type_policy< FORMAT, 1 >
{
public:
  static void input( FORMAT & f, int & align, char * data )
  {
    *data = *( reinterpret_cast<char*>( erf_buffer_access< FORMAT >::require( f, 1) ) );
    ++align;
  }

  static void output( FORMAT & f, int & align, char const * data )
  {
    *( reinterpret_cast<char*>( erf_buffer_access< FORMAT >::desire( f, 1) ) ) = *data;
    ++align;
  }
};

template< class FORMAT >
class erf_type_policy< FORMAT, 2 >
  : public erf_type_policy_impl< FORMAT, 2 >
{
};

template< class FORMAT >
class erf_type_policy< FORMAT, 4 >
  : public erf_type_policy_impl< FORMAT, 4 >
{
};

template< class FORMAT >
class erf_type_policy< FORMAT, 8 >
  : public erf_type_policy_impl< FORMAT, 8 >
{
};


// Macros to keep things neat and tidy in class ERF_format.
#define def_input_simple(type) \
	void input_simple(type& data) \
        { \
          erf_type_policy< This_t, sizeof( type ) >::input(    \
            *this,  \
            this->align,  \
            reinterpret_cast<char*>(&data) );  \
	} 

#define def_output_simple(type) \
	void output_simple(type const& data) \
        { \
          erf_type_policy< This_t, sizeof( type ) >::output(   \
            *this,  \
            this->align,  \
            reinterpret_cast<char const*>(&data) );  \
	} 


// ERF_format class
template <class Buffer>
class ERF_format: public generic_format<Buffer> {
 private:
  typedef ERF_format< Buffer >  This_t;
  int align;

 public:
	typedef Buffer buffer;

  ERF_format(Buffer& buf):generic_format<Buffer>(buf), align( 0 ) {}
	
	template <class Idx>
	void input_start_array(Idx& n) 
        {
          short tmp;
          input_simple( tmp );
          n = (Idx)tmp;
        }

	template <class Idx>
	bool input_end_array(Idx& n) {return n--<=0;}

        // ERF uses null terminated strings.  Find length.
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
	void input_end_string(Idx& n) 
        {
          // The null terminator has not been read.  There may be other
          // characters as well given max_len may have been used.  Advance past
          // the terminator.
          char c;
          do {
            input_simple( c );
          } while ( c != '\0' );
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
                //std::cout << "Read " << std::string( data, size ) << std::endl;
	}

	// This routine is identical to that in GIOP_format
	void input_raw(char* data, int size) {
		int i;
		for(i=0;i<(size>>8)-1;i++,data+=256)
                  memcpy(data, this->require(256), 256);
		int res=size-(i<<8);
		memcpy(data, this->require(res), res);
                align += size;
	}

	template <class Idx>
	void output_start_array(Idx n) {output_simple( (short) n);}
	void output_end_array() {}

  
        // ERF uses null terminated strings.  Do nothing.
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
                align += size;
	}

        inline void input_align( int n )
        {
          int align_incr = ((align % n) ? (n - (align % n)) : 0);
          // just ignore the input
          this->require( align_incr );
          align += align_incr;
        }

        inline void output_align( int n )
        {
          int align_incr = ((align % n) ? (n - (align % n)) : 0);
          std::memset( this->desire( align_incr ), '\0', align_incr );
          align += align_incr;
        }
};

#undef def_input_simple
#undef def_output_simple

#endif
