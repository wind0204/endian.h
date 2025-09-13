/*
 * Utilities related with endianness
 */

#ifndef _ENDIAN_H_
#define _ENDIAN_H_


#include <stdint.h>
#include "util_for_c.h"


__attribute__((always_inline))
static inline uint64_t bswap_64(uint64_t field) {
  field =
    ((field & 0xff00000000000000u) >> 56u) |
    ((field & 0x00ff000000000000u) >> 40u) |
    ((field & 0x0000ff0000000000u) >> 24u) |
    ((field & 0x000000ff00000000u) >>  8u) |
    ((field & 0x00000000ff000000u) <<  8u) |
    ((field & 0x0000000000ff0000u) << 24u) |
    ((field & 0x000000000000ff00u) << 40u) |
    ((field & 0x00000000000000ffu) << 56u);
  return field;
}
__attribute__((always_inline))
static inline uint32_t bswap_32(uint32_t field) {
  field =
    ((field & 0xff000000u) >> 24u) |
    ((field & 0x00ff0000u) >>  8u) |
    ((field & 0x0000ff00u) <<  8u) |
    ((field & 0x000000ffu) << 24u);
  return field;
}
/**
 * BSWAP on 16-bit field is not supported in x86.
 * ROLW, RORW or XCHG are the instructions I wanted compilers to write.
 */
__attribute__((always_inline))
static inline uint16_t bswap_16(uint16_t field) {
  field =
    ((field & 0xff00u) >>  8u) |
    ((field & 0x00ffu) <<  8u);
  return field;
}



// a list of endians
enum util_endian_byte_order : unsigned int {
  util_endian_byte_order_LOCAL,  // used when passing 0 to function to_another_byte_order
  util_endian_LITTLE_ENDIAN, // 1 out of 0x03020100u
  util_endian_BIG_ENDIAN,  // 2 out of 0x00010203u
  util_endian_PDP_ENDIAN,  // 3 out of 0x01000302u (16-bit little-endian)
	util_endian_byte_order_cap
};
//#define util_endian_LITTLE_ENDIAN 1
//#define util_endian_BIG_ENDIAN 2
//#define util_endian_PDP_ENDIAN 3

static const uint32_t ENDIAN_TEST_VALUE = 0x00010203u;
//static uint32_t util_endian_LOCAL_ENDIAN = *(((uint8_t*)&ENDIAN_TEST_VALUE)+2);
#define util_endian_LOCAL_ENDIAN ( *(((uint8_t*)&ENDIAN_TEST_VALUE)+2) )


/**
 * \brief Use this macro to rearrange bytes to another order.
 *
 * param orig_order,new_order An enum util_endian_byte_order, if you set \a orig_order
 *    or \a new_order to 0 (i.e. util_endian_byte_order_LOCAL),
 *    it will be replaced with the corrosponding local endian value.
 * param ptr The pointer to the storage in which you want to rearrange the data.
 * param length The number of bytes you want to rearrange. It must not be an odd number.
 */
__attribute__((always_inline))
static inline void to_another_byte_order(
    enum util_endian_byte_order orig_order, enum util_endian_byte_order new_order,
    void * ptr, unsigned int length) {
  //__ct_assert((orig_order)<util_endian_byte_order_cap && (orig_order)>=1, util_c_lang_bits);
  //__ct_assert(((new_order)<=util_endian_byte_order_cap&& (new_order)>=1), util_c_lang_bits);
  //__ct_assert(!(length&1), util_c_lang_bits);

  if ( orig_order == 0 ) {
    orig_order = util_endian_LOCAL_ENDIAN;
  }
  if ( new_order == 0 ) {
    new_order = util_endian_LOCAL_ENDIAN;
  }

  if ( orig_order != new_order ) {
    unsigned int i, j;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
    switch ( new_order ) {
      case util_endian_LITTLE_ENDIAN:
        if (orig_order == util_endian_BIG_ENDIAN) {
reverse_order:
          switch ( length ) {
            case 8:
              *(uint64_t*)ptr = bswap_64(*(uint64_t*)ptr);
              break;
            case 4:
              *(uint32_t*)ptr = bswap_32(*(uint32_t*)ptr);
              break;
            case 2:
              *(uint16_t*)ptr = bswap_16(*(uint16_t*)ptr);
              break;
            default:
              for (i=0, j=(length)-1; i<j; i++, j--) {
                _swap((uint8_t*)(ptr)+i, (uint8_t*)(ptr)+j)
              }
              break;
          }
        } else {
          for (i=0, j=((length)>>1)-1; i<j; i++, j--) {
            _swap((uint16_t*)(ptr)+i, (uint16_t*)(ptr)+j)
          }
        }
        break;
      case util_endian_BIG_ENDIAN:
        if (orig_order == util_endian_LITTLE_ENDIAN) {
          goto reverse_order;
        } else {
          for (i=0, j=1; j<(length); i=++j, j++) {
            _swap((uint8_t*)(ptr)+i, (uint8_t*)(ptr)+j)
          }
        }
        break;
      case util_endian_PDP_ENDIAN:
        if (orig_order == util_endian_BIG_ENDIAN) {
          for (i=0, j=1; j<(length); i=++j, j++) {
            _swap((uint8_t*)(ptr)+i, (uint8_t*)(ptr)+j)
          }
        } else {
          for (i=0, j=((length)>>1)-1; i<j; i++, j--) {
            _swap((uint16_t*)(ptr)+i, (uint16_t*)(ptr)+j)
          }
        }
        break;
      default:
        break;
    }
#pragma GCC diagnostic pop
  }
}


#endif //_ENDIAN_H_
