/*
 * Automatic configuration file for XTL
 *
 * Copyright (C) 2000 Asger Nielsen, alstrup@sophusmedical.dk
 * Copyright (C) 2000 Angus Leeming, a.leeming@ic.ac.uk
 * Copyright (C) 2000 Jose' Orlando Pereira, jop@di.uminho.pt
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
 * $Id: config.h,v 1.10 2010/08/05 16:51:14 uid186296 Exp $
 */

#ifndef __XTL_CONFIG
#define __XTL_CONFIG

#define XTL_CONFIG_CHOICE_MACROS

#if defined(__GNUC__) 
#	if __GNUC__ >2 || ( __GNUC__ == 2 && __GNUC_MINOR__ >=95 ) // >= G++ 2.95
#		define XTL_CONFIG_SIMPLE_CONTAINERS
#	endif

	typedef long long longlong;
	typedef unsigned long long unsignedlonglong;

#elif defined (__DECCXX)
#      	define XTL_CONFIG_SIMPLE_CONTAINERS

	typedef long long int longlong;
	typedef unsigned long long int unsignedlonglong;

#elif defined (__sgi)
#      	define XTL_CONFIG_SIMPLE_CONTAINERS

	typedef long long int longlong;
	typedef unsigned long long int unsignedlonglong;

#elif defined (_WIN32)

#       if defined(_MSC_VER) && _MSC_VER <= 1200  // VC6 or older
#           define XTL_CONFIG_COMPOSITE_BUG
            // Work around for broken for-scoping with Visual C++ 6.0
#           define for if(0);else for
#       else
#           define XTL_CONFIG_SIMPLE_CONTAINERS
#       endif
#	define XTL_CONFIG_LACK_ENDIAN_H

	typedef __int64  longlong;
	typedef unsigned __int64  unsignedlonglong;

	// Disable some stupid warnings
#	pragma warning(disable:4127 4786 4800)

	// Enable a bunch of useful warnings
#	pragma warning(3:4019 4032 4057 4061 4125 4130 4152 4189 4201 4706)

#else
#if HAVE_LONG_LONG
	typedef long long longlong;
	typedef unsigned long long unsignedlonglong;
#endif
#endif

// Establish __BYTE_ORDER
#ifdef __linux__
#	include <endian.h>
#else
#	define __LITTLE_ENDIAN 1234
#	define __BIG_ENDIAN    4321
#endif

#if defined(__alpha) || defined(__alpha__)
#	ifndef __BYTE_ORDER
#		define __BYTE_ORDER __LITTLE_ENDIAN
#	endif
                                            
#elif defined __sgi
#	ifndef __BYTE_ORDER
#		define __BYTE_ORDER __BIG_ENDIAN
#	endif

#elif defined _WIN32
#	ifndef __BYTE_ORDER
#		define __BYTE_ORDER __LITTLE_ENDIAN
#	endif

#endif

// Cygwin
#ifdef __CYGWIN__
#    include <sys/param.h>
#    ifdef BYTE_ORDER
#      if (BYTE_ORDER == LITTLE_ENDIAN)
#        define __BYTE_ORDER __LITTLE_ENDIAN
#      else
#        define __BYTE_ORDER __BIG_ENDIAN
#      endif
#    else
#      error "Byte Order not defined."
#    endif
#endif

#if ((__BYTE_ORDER != __LITTLE_ENDIAN) && (__BYTE_ORDER != __BIG_ENDIAN))
#	error "Architecture not supported."
#endif

// Don't use byteswap.h on Alpha machines because its buggy
#if defined(__linux__) && !(defined(__alpha) || defined(__alpha__))
#	include <byteswap.h>
#else
inline unsigned short bswap_16(unsigned short b) {
        return ((b&0xff00)>>8)|((b&0x00ff)<<8);
}

inline unsigned int bswap_32(unsigned int b) {
	return ((b&0xff000000)>>24)|((b&0x00ff0000)>>8)|
		((b&0x0000ff00)<<8)|((b&0x000000ff)<<24);
}

inline unsignedlonglong bswap_64(unsignedlonglong b) { 
	return ( ((b&0xff00000000000000LL) >> 56) |
		 ((b&0x00ff000000000000LL) >> 40) |
		 ((b&0x0000ff0000000000LL) >> 24) |
		 ((b&0x000000ff00000000LL) >> 8) |
		 ((b&0x00000000ff000000LL) << 8) |
		 ((b&0x0000000000ff0000LL) << 24) |
		 ((b&0x000000000000ff00LL) << 40) |
		 ((b&0x00000000000000ffLL) << 56) );
}
#endif

// We need this for memcpy
#if (defined(__alpha) || defined(__alpha__)) && !defined(__GNUC__)
#include <string.h>
#else
#include <cstring>
#endif


// data is stored with big endian ordering
// this must be global due to a joint g++/glibc/i386 "feature"
#if (__BYTE_ORDER == __LITTLE_ENDIAN)
inline void _xtl_big_end_16(char const* in, char* out ) {
	*reinterpret_cast<unsigned short*>(out) = \
      bswap_16( *reinterpret_cast<const unsigned short*>( in ) );
}

inline void _xtl_big_end_32(char const* in, char* out ) {
	*reinterpret_cast<unsigned int*>(out) = \
      bswap_32( *reinterpret_cast<const unsigned int*>( in ) );
}

inline void _xtl_big_end_64(char const* in, char* out ) {
	*reinterpret_cast<unsignedlonglong*>(out) = \
      bswap_64( *reinterpret_cast<const unsignedlonglong*>( in ) );
}
#elif (__BYTE_ORDER == __BIG_ENDIAN)
inline void _xtl_big_end_16(char const* in, char* out ) {
	*reinterpret_cast<unsigned short*>(out) = \
      *reinterpret_cast<const unsigned short*>( in );
}

inline void _xtl_big_end_32(char const* in, char* out ) {
	*reinterpret_cast<unsigned int*>(out) = \
      *reinterpret_cast<const unsigned int*>( in );
}

inline void _xtl_big_end_64(char const* in, char* out ) {
	*reinterpret_cast<unsignedlonglong*>(out) = \
      *reinterpret_cast<const unsignedlonglong*>( in );
}
#endif
 
template< int i >
inline void _xtl_big_end( char const* in, char* out );
 
template<>
inline void _xtl_big_end< 1 >( char const* in, char* out )
{
  *out = *in;
}
 
template<>
inline void _xtl_big_end< 2 >( char const* in, char* out )
{
  _xtl_big_end_16( in, out );
}
 
template<>
inline void _xtl_big_end< 4 >( char const* in, char* out )
{
  _xtl_big_end_32( in, out );
}
 
template<>
inline void _xtl_big_end< 8 >( char const* in, char* out )
{
  _xtl_big_end_64( in, out );
}

#endif
