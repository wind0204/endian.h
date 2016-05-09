/*
 * Utilities related with endianness
 */

#ifndef _ENDIAN_H_
#define _ENDIAN_H_


#include <stdint.h>
#include "util_for_c.h"


// a simple number will help you to determine your endian
const uint32_t ENDIAN_TEST_VALUE = 0x00010203ul;

// a list of endians
enum endianness {
  LITTLE_ENDIAN=1, //0x03020100ul
  BIG_ENDIAN, //0x00010203ul
  PDP_ENDIAN //0x01000302ul (16-bit little-endian)
};

// your processor's endian
#define __ENDIAN ( *((uint8_t*)&ENDIAN_TEST_VALUE+2) )

/*
 * __to_another_endian(from, to, bit_array, length)
 * from/to : enum endianness, if you specify 'from' as 0, it will be changed to __ENDIAN (i.e. your processor's endian)
 * bit_array : pointer to a storage that you want to rearrange
 */
#define __impl_to_another_endian(from, to, bit_array, length)\
{\
  __ct_assert( !(length&1) &&\
      ((from)<=3 && (from)>=1) &&\
      ( ((to)<=3 && (to)>=1) ) )\
  if ( from != to ) {\
    int_fast8_t _i, _j;\
    switch (to) {\
      case LITTLE_ENDIAN:\
        if (from == BIG_ENDIAN) {\
          for (_i=0, _j=(length)-1; _i<_j; _i++, _j--) {\
            __swap((uint8_t*)(bit_array)+_i, (uint8_t*)(bit_array)+_j)\
          }\
        } else {\
          for (_i=0, _j=((length)>>1)-1; _i<_j; _i++, _j--) {\
            __swap((uint16_t*)(bit_array)+_i, (uint16_t*)(bit_array)+_j)\
          }\
        }\
        break;\
      case BIG_ENDIAN:\
        if (from == LITTLE_ENDIAN) {\
          for (_i=0, _j=(length)-1; _i<_j; _i++, _j--) {\
            __swap((uint8_t*)(bit_array)+_i, (uint8_t*)(bit_array)+_j)\
          }\
        } else {\
          for (_i=0, _j=1; _j<(length); _i=++_j, _j++) {\
            __swap((uint8_t*)(bit_array)+_i, (uint8_t*)(bit_array)+_j)\
          }\
        }\
        break;\
      case PDP_ENDIAN:\
        if (from == BIG_ENDIAN) {\
          for (_i=0, _j=1; _j<(length); _i=++_j, _j++) {\
            __swap((uint8_t*)(bit_array)+_i, (uint8_t*)(bit_array)+_j)\
          }\
        } else {\
          for (_i=0, _j=((length)>>1)-1; _i<_j; _i++, _j--) {\
            __swap((uint16_t*)(bit_array)+_i, (uint16_t*)(bit_array)+_j)\
          }\
        }\
        break;\
    }\
  }\
}
#define __to_another_endian(from, to, bit_array, length)\
  __impl_to_another_endian((from?from:__ENDIAN), to, bit_array, length)


#endif //_ENDIAN_H_
