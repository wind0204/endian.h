/*
 * Test endian.h
 */


#include "endian.h"
#include <stdint.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
  {
    uint64_t buffer;
    printf("__ENDIAN = %d\n", __ENDIAN);

    buffer = 0x0102030405060708u;
    printf("0x0102030405060708u is stored as --%02d-%02d-%02d-%02d-%02d-%02d-%02d-%02d->\n",
        *(uint8_t*)&buffer, *((uint8_t*)&buffer+1), *((uint8_t*)&buffer+2), *((uint8_t*)&buffer+3),
        *((uint8_t*)&buffer+4), *((uint8_t*)&buffer+5), *((uint8_t*)&buffer+6), *((uint8_t*)&buffer+7));
    __to_another_endian(0, PDP_ENDIAN, &buffer, 8)
    printf("__to_another_endian(0, PDP_ENDIAN, &buffer, 8) = --%02d-%02d-%02d-%02d-%02d-%02d-%02d-%02d->\n",
        *(uint8_t*)&buffer, *((uint8_t*)&buffer+1), *((uint8_t*)&buffer+2), *((uint8_t*)&buffer+3),
        *((uint8_t*)&buffer+4), *((uint8_t*)&buffer+5), *((uint8_t*)&buffer+6), *((uint8_t*)&buffer+7));
    __to_another_endian(PDP_ENDIAN, LITTLE_ENDIAN, &buffer, 8)
    printf("__to_another_endian(PDP_ENDIAN, LITTLE_ENDIAN, &buffer, 8) = --%02d-%02d-%02d-%02d-%02d-%02d-%02d-%02d->\n",
        *(uint8_t*)&buffer, *((uint8_t*)&buffer+1), *((uint8_t*)&buffer+2), *((uint8_t*)&buffer+3),
        *((uint8_t*)&buffer+4), *((uint8_t*)&buffer+5), *((uint8_t*)&buffer+6), *((uint8_t*)&buffer+7));
    __to_another_endian(LITTLE_ENDIAN, BIG_ENDIAN, &buffer, 8)
    printf("__to_another_endian(LITTLE_ENDIAN, BIG_ENDIAN, &buffer, 8) = --%02d-%02d-%02d-%02d-%02d-%02d-%02d-%02d->\n",
        *(uint8_t*)&buffer, *((uint8_t*)&buffer+1), *((uint8_t*)&buffer+2), *((uint8_t*)&buffer+3),
        *((uint8_t*)&buffer+4), *((uint8_t*)&buffer+5), *((uint8_t*)&buffer+6), *((uint8_t*)&buffer+7));
    __to_another_endian(BIG_ENDIAN, PDP_ENDIAN, &buffer, 8)
    printf("__to_another_endian(BIG_ENDIAN, PDP_ENDIAN, &buffer, 8) = --%02d-%02d-%02d-%02d-%02d-%02d-%02d-%02d->\n",
        *(uint8_t*)&buffer, *((uint8_t*)&buffer+1), *((uint8_t*)&buffer+2), *((uint8_t*)&buffer+3),
        *((uint8_t*)&buffer+4), *((uint8_t*)&buffer+5), *((uint8_t*)&buffer+6), *((uint8_t*)&buffer+7));
    __to_another_endian(PDP_ENDIAN, BIG_ENDIAN, &buffer, 8)
    printf("__to_another_endian(PDP_ENDIAN, BIG_ENDIAN, &buffer, 8) = --%02d-%02d-%02d-%02d-%02d-%02d-%02d-%02d->\n",
        *(uint8_t*)&buffer, *((uint8_t*)&buffer+1), *((uint8_t*)&buffer+2), *((uint8_t*)&buffer+3),
        *((uint8_t*)&buffer+4), *((uint8_t*)&buffer+5), *((uint8_t*)&buffer+6), *((uint8_t*)&buffer+7));
    __to_another_endian(BIG_ENDIAN, LITTLE_ENDIAN, &buffer, 8)
    printf("__to_another_endian(BIG_ENDIAN, LITTLE_ENDIAN, &buffer, 8) = --%02d-%02d-%02d-%02d-%02d-%02d-%02d-%02d->\n",
        *(uint8_t*)&buffer, *((uint8_t*)&buffer+1), *((uint8_t*)&buffer+2), *((uint8_t*)&buffer+3),
        *((uint8_t*)&buffer+4), *((uint8_t*)&buffer+5), *((uint8_t*)&buffer+6), *((uint8_t*)&buffer+7));
  }

  /*
  {
    printf("%f -> %f\n", -1.0f, _fabsf(-1.0f));
    printf("%f -> %f\n", -1.0, _fabsd(-1.0));
  }

  {
    uint8_t array[8];
    printf("array_len = %ld\n", __get_array_len(array));
  }

  {
    uint_fast32_t buffer = 9;
    printf("__align_to_power_of_two(%ld, 8) = %ld\n", buffer, __align_to_power_of_two(buffer, 8));
    printf("__align_to_power_of_two(%ld, 16) = %ld\n", buffer, __align_to_power_of_two(buffer, 16));
    printf("__is_aligned_to_power_of_two(%ld, 8) = %d\n", buffer, __is_aligned_to_power_of_two(buffer, 8));
    printf("__is_aligned_to_power_of_two(%ld, 16) = %d\n", buffer, __is_aligned_to_power_of_two(buffer, 16));
  }

  {
    struct a_struct{
      int8_t i8;
      int16_t i16;
      int32_t i32;
      int64_t i64;
      char last_field;
    } a_struct;
    printf("struct a_struct { int8_t i8; int16_t i16; int32_t i32; int64_t i64; char last_field; } a_struct;\n");
    printf("__get_field_offset(a_struct, i8) = %ld\n", __get_field_offset(a_struct, i8));
    printf("__get_field_offset(a_struct, i16) = %ld\n", __get_field_offset(a_struct, i16));
    printf("__get_field_offset(a_struct, i32) = %ld\n", __get_field_offset(a_struct, i32));
    printf("__get_field_offset(a_struct, i64) = %ld\n", __get_field_offset(a_struct, i64));
    printf("__get_field_offset(a_struct, last_field) = %ld\n", __get_field_offset(a_struct, last_field));
  }
  */

  return 0;
}
