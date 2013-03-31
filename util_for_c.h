/*
 * Miscellaneous utilities for C programming language
 */

#ifndef _UTIL_FOR_C_H_
#define _UTIL_FOR_C_H_


#include <stdint.h>


// A compile time assertion check
#define __paste(foo,bar) (foo##bar)
#define __ct_assert_with_info(predication, info) \
	typedef char __paste(ct_assertion_failed_at_,info)[(predication)?1:-1];
#define __ct_assert(predication) \
	__ct_assert_with_info((predication), __LINE__)


// Obtain the number of elements in the given C array
#define __get_array_len(array) ( sizeof(array) / sizeof((array)[0]) )


// Align the supplied size to the specified power_of_two
#define __align_to_power_of_two(n_to_align, power_of_two) \
	( ((n_to_align)+(power_of_two)-1) & ~((power_of_two)-1) )

// Check whether the supplied size is aligned to the specified power_of_two
#define __is_aligned_to_power_of_two(n_to_test, power_of_two) \
	( ((n_to_test) & ((power_of_two)-1)) == 0 )


// Obtain the offset of a field in a structure
#define __get_field_offset(struct_name, field_name) \
	( (uint_fast32_t)(0+&(((struct struct_name*)NULL)->field_name)) )

// Obtain the struct element at the specified offset given the struct ptr
/* #define __get_field_ptr(struct_ptr, offset) \
	( (void*)(((int8_t*)struct_ptr)+(offset)) ) */


// Swap
#define __swap(p1,p2) *(p1) ^= *(p2); *(p2) ^= *(p1); *(p1) ^= *(p2);


// unions for floating numbers
union union64 {
	uint64_t ui;
	int64_t i;
	double f;
};
union union32 {
	uint32_t ui;
	int32_t i;
	float f;
};


// Obtain the absolute value of the given value
inline double _fabsd(double d)
{
	union union64 ret;
	ret.f = d;
	ret.ui &= 0x7fffffffffffffff;
	return ret.f;
}
inline float _fabsf(float f)
{
	union union32 ret;
	ret.f = f;
	ret.ui &= 0x7fffffffu;
	return ret.f;
}


#endif //_UTIL_FOR_C_H_
