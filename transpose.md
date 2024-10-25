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

`bitmap_transpose` function extract one column of 8 bits with bit shift and mask, then bit shift them to diagnal positions, and then pairwise add all rows to get final result.

`bitmap_transpose` only uses 64 bit width NEON instructions. `bitmap_transpose_2` uses full 128 bit width and is faster.

```*/

#include <iostream>
#include <bitset>

#include <arm_neon.h>

#include "timer.hpp"

void print_8x8(uint8_t a[8]) {
    for(int i = 0; i < 8; i++) {
        std::cout << std::bitset<8>(a[i]) << std::endl;
    }
    std::cout << std::endl;
}

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

    uint8x8_t col_0 = vshl_u8(vand_u8(vshr_n_u8(a, 7), mask), shift_factors);
    uint8x8_t col_1 = vshl_u8(vand_u8(vshr_n_u8(a, 6), mask), shift_factors);
    uint8x8_t col_2 = vshl_u8(vand_u8(vshr_n_u8(a, 5), mask), shift_factors);
    uint8x8_t col_3 = vshl_u8(vand_u8(vshr_n_u8(a, 4), mask), shift_factors);
    uint8x8_t col_4 = vshl_u8(vand_u8(vshr_n_u8(a, 3), mask), shift_factors);
    uint8x8_t col_5 = vshl_u8(vand_u8(vshr_n_u8(a, 2), mask), shift_factors);
    uint8x8_t col_6 = vshl_u8(vand_u8(vshr_n_u8(a, 1), mask), shift_factors);
    uint8x8_t col_7 = vshl_u8(vand_u8(a, mask), shift_factors);

    uint8x8_t row_01 = vpadd_u8(col_0, col_1); 
    uint8x8_t row_23 = vpadd_u8(col_2, col_3); 
    uint8x8_t row_45 = vpadd_u8(col_4, col_5); 
    uint8x8_t row_67 = vpadd_u8(col_6, col_7);

    uint8x8_t row_0123 = vpadd_u8(row_01, row_23);
    uint8x8_t row_4567 = vpadd_u8(row_45, row_67);

    uint8x8_t result = vpadd_u8(row_0123, row_4567);
    return result;
}


uint8x8_t bitmap_transpose_2(uint8x8_t a) {
    uint8x16_t mask = vdupq_n_u8(0x01);
    int8x16_t shift_factors = {7, 6, 5, 4, 3, 2, 1, 0, 7, 6, 5, 4, 3, 2, 1, 0};
    uint8x16_t aa = vcombine_u8(vshr_n_u8(a, 1), a);

    uint8x16_t col_01 = vandq_u8(vshrq_n_u8(aa, 6), mask);
    uint8x16_t col_23 = vandq_u8(vshrq_n_u8(aa, 4), mask);
    uint8x16_t col_45 = vandq_u8(vshrq_n_u8(aa, 2), mask);
    uint8x16_t col_67 = vandq_u8(aa, mask);

    uint8x16_t row_01 = vshlq_u8(col_01, shift_factors);
    uint8x16_t row_23 = vshlq_u8(col_23, shift_factors);
    uint8x16_t row_45 = vshlq_u8(col_45, shift_factors);
    uint8x16_t row_67 = vshlq_u8(col_67, shift_factors);

    uint8x16_t row_0123 = vpaddq_u8(row_01, row_23); 
    uint8x16_t row_4567 = vpaddq_u8(row_45, row_67); 

    uint8x16_t result = vpaddq_u8(row_0123, row_4567);
    result = vpaddq_u8(result, result);
    return vget_low_u8(result);
}

int main() {
    uint8_t w[8] = {
        0b11111111,
        0b01000000,
        0b01000000,
        0b01111110,
        0b01000000,
        0b01000000,
        0b01000000,
        0b11100000
    };
    uint8_t t[8];

    std::cout << "Original bitmap:" << std::endl;
    print_8x8(w);
    
    { 
        volatile uint8x8_t ww = vld1_u8(w);
        volatile uint8x8_t tt;
        AutoTimer at("Transpose v1");
        for (int i = 0; i < 2750000; i++) {
            tt = bitmap_transpose(ww);
        }
        vst1_u8(t, tt); 
    }
    print_8x8(t);

    { 
        volatile uint8x8_t ww = vld1_u8(w);
        volatile uint8x8_t tt;
        AutoTimer at("Transpose v2");
        for (int i = 0; i < 2750000; i++) {
            tt = bitmap_transpose_2(ww);
        }
        vst1_u8(t, tt);
    }
    print_8x8(t);
}

