/* 
    RawSpeed - RAW file decoder.

    Copyright (C) 2009 Klaus Post

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

    http://www.klauspost.com
*/
#pragma once

#if !defined(__unix__) && !defined(__MINGW32__)
#include <intrin.h>
#pragma intrinsic(_ReturnAddress)
#define MIN(a,b) min(a,b)
#define MAX(a,b) max(a,b)
#else // On linux
#define _ASSERTE(a) void(a)
#define _RPT0(a,b) 
#define _RPT1(a,b,c) 
#define _RPT2(a,b,c,d) 
#define _RPT3(a,b,c,d,e) 
#define _RPT4(a,b,c,d,e,f) 
#define __inline inline
#define _strdup(a) strdup(a)
#define _aligned_malloc(a, alignment) malloc(a)
#define _aligned_free(a) do { free(a); } while (0)
#ifndef MIN
#define MIN(a, b)  lmin(a,b)
#endif
#ifndef MAX
#define MAX(a, b)  lmin(a,b)
#endif
#ifndef __MINGW32__
typedef char* LPCWSTR;
#endif
#endif // __unix__

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

int rawspeed_get_number_of_processor_cores();


namespace RawSpeed {

typedef signed char char8;
typedef unsigned char uchar8;
typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned short ushort16;

inline void BitBlt(uchar8* dstp, int dst_pitch, const uchar8* srcp, int src_pitch, int row_size, int height) {
  if (height == 1 || (dst_pitch == src_pitch && src_pitch == row_size)) {
    memcpy(dstp, srcp, row_size*height);
    return;
  }
  for (int y=height; y>0; --y) {
    memcpy(dstp, srcp, row_size);
    dstp += dst_pitch;
    srcp += src_pitch;
  }
}
inline bool isPowerOfTwo (int val) {
  return (val & (~val+1)) == val;
}

inline int lmin(int p0, int p1) {
  return p1 + ((p0 - p1) & ((p0 - p1) >> 31));
}
inline int lmax(int p0, int p1) {
  return p0 - ((p0 - p1) & ((p0 - p1) >> 31));
}

inline uint32 getThreadCount()
{
#ifdef WIN32
  return pthread_num_processors_np();
#else
  return rawspeed_get_number_of_processor_cores();
#endif
}

inline uint32 clampbits(int x, uint32 n) { uint32 _y_temp; if( (_y_temp=x>>n) ) x = ~_y_temp >> (32-n); return x;}


} // namespace RawSpeed
