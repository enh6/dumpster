    #if 0
    g++ -x c++ $0 -march=native -Wall -O2 -o test
    ./test
    exit 0

<!--
#endif
/* -->

# Transpose 8x8 bitmap with NEON

`bash transpose.md` to build and run this c++ program.

A 8x8 bitmap has 64 bits and is stored in a `uint8x8_t`.

`bitmap_transpose` function extract one column of 8 bits with bit shift and mask, then bit shift them to diagnal positions, and then reduce sum to a `uint8_t`.

`bitmap_transpose` only uses 64 bit width NEON instructions. `bitmap_transpose_2` uses full 128 bit width and is faster.

```*/

#include <iostream>
#include <bitset>

#include <arm_neon.h>

#include "timer.hpp"

void print(uint8x8_t a) {
    std::cout << std::bitset<8>(vget_lane_u8(a, 0)) << std::endl;
    std::cout << std::bitset<8>(vget_lane_u8(a, 1)) << std::endl;
    std::cout << std::bitset<8>(vget_lane_u8(a, 2)) << std::endl;
    std::cout << std::bitset<8>(vget_lane_u8(a, 3)) << std::endl;
    std::cout << std::bitset<8>(vget_lane_u8(a, 4)) << std::endl;
    std::cout << std::bitset<8>(vget_lane_u8(a, 5)) << std::endl;
    std::cout << std::bitset<8>(vget_lane_u8(a, 6)) << std::endl;
    std::cout << std::bitset<8>(vget_lane_u8(a, 7)) << std::endl;
    std::cout << std::endl;
}

void print(uint16x8_t a) {
    std::cout << std::bitset<16>(vgetq_lane_u16(a, 0)) << std::endl;
    std::cout << std::bitset<16>(vgetq_lane_u16(a, 1)) << std::endl;
    std::cout << std::bitset<16>(vgetq_lane_u16(a, 2)) << std::endl;
    std::cout << std::bitset<16>(vgetq_lane_u16(a, 3)) << std::endl;
    std::cout << std::bitset<16>(vgetq_lane_u16(a, 4)) << std::endl;
    std::cout << std::bitset<16>(vgetq_lane_u16(a, 5)) << std::endl;
    std::cout << std::bitset<16>(vgetq_lane_u16(a, 6)) << std::endl;
    std::cout << std::bitset<16>(vgetq_lane_u16(a, 7)) << std::endl;
    std::cout << std::endl;
}

void print(uint8x16_t a) {
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 0)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 1)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 2)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 3)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 4)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 5)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 6)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 7)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 8)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 9)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 10)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 11)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 12)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 13)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 14)) << std::endl;
    std::cout << std::bitset<8>(vgetq_lane_u8(a, 15)) << std::endl;
    std::cout << std::endl;
}

uint8x8_t bitmap_transpose(uint8x8_t a) {
    uint8x8_t mask = vdup_n_u8(0x01);
    int8x8_t shift_factors = {7, 6, 5, 4, 3, 2, 1, 0};

    uint8x8_t col_0 = vand_u8(vshr_n_u8(a, 7), mask);
    uint8x8_t col_1 = vand_u8(vshr_n_u8(a, 6), mask);
    uint8x8_t col_2 = vand_u8(vshr_n_u8(a, 5), mask);
    uint8x8_t col_3 = vand_u8(vshr_n_u8(a, 4), mask);
    uint8x8_t col_4 = vand_u8(vshr_n_u8(a, 3), mask);
    uint8x8_t col_5 = vand_u8(vshr_n_u8(a, 2), mask);
    uint8x8_t col_6 = vand_u8(vshr_n_u8(a, 1), mask);
    uint8x8_t col_7 = vand_u8(a, mask);

    uint8_t row_0 = vaddv_u8(vshl_u8(col_0, shift_factors)); 
    uint8_t row_1 = vaddv_u8(vshl_u8(col_1, shift_factors)); 
    uint8_t row_2 = vaddv_u8(vshl_u8(col_2, shift_factors)); 
    uint8_t row_3 = vaddv_u8(vshl_u8(col_3, shift_factors)); 
    uint8_t row_4 = vaddv_u8(vshl_u8(col_4, shift_factors)); 
    uint8_t row_5 = vaddv_u8(vshl_u8(col_5, shift_factors)); 
    uint8_t row_6 = vaddv_u8(vshl_u8(col_6, shift_factors)); 
    uint8_t row_7 = vaddv_u8(vshl_u8(col_7, shift_factors)); 
    uint8x8_t result = {row_0, row_1, row_2, row_3, row_4, row_5, row_6, row_7};
    return result;
}

uint8x8_t bitmap_transpose_2(uint8x8_t a) {
    uint8x16_t mask = vdupq_n_u8(0x01);
    int8x16_t shift_factors = {7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0};
    uint8x16_t aa = vcombine_u8(a, vdup_n_u8(0));
    uint8x16_t shr = vcombine_u8(vshr_n_u8(a, 1), vdup_n_u8(0));
    uint8x16_t zip = vzip1q_u8(shr, aa);

    uint8x16_t col_01 = vandq_u8(vshrq_n_u8(zip, 6), mask);
    uint8x16_t col_23 = vandq_u8(vshrq_n_u8(zip, 4), mask);
    uint8x16_t col_45 = vandq_u8(vshrq_n_u8(zip, 2), mask);
    uint8x16_t col_67 = vandq_u8(zip, mask);

    uint16_t row_01 = vaddvq_u16(vreinterpretq_u16_u8(vshlq_u8(col_01, shift_factors)));
    uint16_t row_23 = vaddvq_u16(vreinterpretq_u16_u8(vshlq_u8(col_23, shift_factors)));
    uint16_t row_45 = vaddvq_u16(vreinterpretq_u16_u8(vshlq_u8(col_45, shift_factors)));
    uint16_t row_67 = vaddvq_u16(vreinterpretq_u16_u8(vshlq_u8(col_67, shift_factors)));
    uint16x4_t r = {row_01, row_23, row_45, row_67};
    uint8x8_t result = vreinterpret_u8_u16(r);
    return result;
}

int main() {
    volatile uint8x8_t w = {
        0b11111111,
        0b01000000,
        0b01000000,
        0b01111110,
        0b01000000,
        0b01000000,
        0b01000000,
        0b11100000
    };
    volatile uint8x8_t t;
    std::cout << "Original bitmap:" << std::endl;
    print(w);
    
    { 
        AutoTimer at("Transpose v1");
        for (int i = 0; i < 2750000; i++) {
            t = bitmap_transpose(w);
        }
    }
    print(t);

    { 
        AutoTimer at("Transpose v2");
        for (int i = 0; i < 2750000; i++) {
            t = bitmap_transpose_2(w);
        }
    }
    print(t);
}
