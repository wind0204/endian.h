/*
 * Miscellaneous utilities for C programming language
 */

#ifndef _UTIL_FOR_C_H_
#define _UTIL_FOR_C_H_


#include <stdint.h>
#include <assert.h>


// unions
union union64 {
  uint64_t u;
  int64_t i;
  double f;
};
union union32 {
  uint32_t u;
  int32_t i;
  float f;
};
union union16 {
  uint16_t u;
  int16_t i;
};
union union8 {
  uint8_t u;
  int8_t i;
};


/**
 * \brief I've seen this be compiled into one xchg instruction in gcc 4.6.3 Athlon X2
 */
#define _xorswap(p1,p2) *(p1) ^= *(p2); *(p2) ^= *(p1); *(p1) ^= *(p2);

/**
 * A quote: "Most modern compilers can optimize the temporary variable in the naive swap,
 * in which case the naive swap uses the same amount of memory and the same number of registers
 * as the _xorswap does and is at least as fast, and often faster."
 */
#define _swap(p1,p2)\
{\
  assert( sizeof(*(p2)) == sizeof(*(p1)) );\
  typeof(*(p1)) _tmpvar = *(p1);\
  *(p1) = *(p2);\
  *(p2) = _tmpvar;\
}

/**
 * \brief Obtain the number of elements in the given C array
 */
#define _arr_elem_cnt(array) \
  ( sizeof(array) / sizeof(array[0]) )

/**
 * \brief Align the given length to the specified \a power_of_two, rounding down.
 * \a n_to_align must be greater than 0 and \a power_of_two must be a power of two
 */
#define _align_to_power_of_two_downward(n_to_align, power_of_two) \
  ( (n_to_align) & ~((power_of_two)-1) )
#define _align_ptr_to_power_of_two(ptr, power_of_two) \
{\
  uintptr_t n_to_align = (uintptr_t)(ptr);\
  (ptr) = (void*)_align_to_power_of_two( n_to_align, (power_of_two) );\
}
#define _align_ptr(ptr) \
{\
  _align_ptr_to_power_of_two( ptr, alignof(typeof(*(ptr))) );\
}

/**
 * \brief Check whether the given length is aligned to the specified \a power_of_two
 * \a n_to_test must be greater than 0 and \a power_of_two must be a power of two
 */
#define _is_aligned_to_power_of_two(n_to_test, power_of_two) \
  ( ((n_to_test) & ((power_of_two)-1)) == 0 )

/**
 * \brief Check whether the given length is aligned to the specified \a power_of_two
 * \a n_to_test must be greater than 0
 */
#define _is_power_of_two(n_to_test) \
  ( ((n_to_test) & ((n_to_test)-1)) == 0 )


/**
 * \brief Obtain the offset of a field in a structure
 */
#ifndef offsetof
#define offsetof(the_struct, field_name) \
  ( (uint_fast16_t) (0 + &((the_struct*)0)->field_name) )
#endif


/**
 * \brief Obtain the offset of a field in a structure
 */
#ifndef offsetof
#define offsetof(the_struct, field_name) \
  ( (uint_fast16_t) (0 + &((the_struct*)0)->field_name) )
#endif


#endif //_UTIL_FOR_C_H_
