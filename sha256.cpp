#if 0
g++ -std=c++14 -Wall -O3 -o sha256 $0
exit
#endif

#include <cstdint>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>

const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

uint32_t x[64], digest[8];

inline uint32_t swap_byte_order(uint32_t x) {
  return ((x << 24) & 0xff000000) | ((x << 8) & 0x00ff0000) |
         ((x >> 8) & 0x0000ff00) | ((x >> 24) & 0x000000ff);
}

void process() {
  uint32_t a = digest[0], b = digest[1], c = digest[2], d = digest[3],
           e = digest[4], f = digest[5], g = digest[6], h = digest[7];

  auto R = [](auto x, auto n) { return (x >> n) | (x << (32 - n)); };

  for (int i = 0; i < 16; i++) {
    x[i] = swap_byte_order(x[i]);
  }
  for (int i = 16; i < 64; i++) {
    uint32_t s0 = R(x[i - 15], 7) ^ R(x[i - 15], 18) ^ (x[i - 15] >> 3);
    uint32_t s1 = R(x[i - 2], 17) ^ R(x[i - 2], 19) ^ (x[i - 2] >> 10);
    x[i] = x[i - 16] + x[i - 7] + s0 + s1;
  }

  for (int i = 0; i < 64; i++) {
    uint32_t tmp1 = (R(e, 6) ^ R(e, 11) ^ R(e, 25)) + ((e & f) ^ (~e & g)) + h +
                    x[i] + k[i];
    uint32_t tmp2 =
        (R(a, 2) ^ R(a, 13) ^ R(a, 22)) + ((a & b) ^ (a & c) ^ (b & c));
    h = g;
    g = f;
    f = e;
    e = d + tmp1;
    d = c;
    c = b;
    b = a;
    a = tmp1 + tmp2;
  }

  digest[0] += a;
  digest[1] += b;
  digest[2] += c;
  digest[3] += d;
  digest[4] += e;
  digest[5] += f;
  digest[6] += g;
  digest[7] += h;
}

void sha1(std::istream &is, std::ostream &os) {
  uint64_t length = 0;
  bool reach_eof = false;
  char *chunk = reinterpret_cast<char *>(x);
  digest[0] = 0x6a09e667;
  digest[1] = 0xbb67ae85;
  digest[2] = 0x3c6ef372;
  digest[3] = 0xa54ff53a;
  digest[4] = 0x510e527f;
  digest[5] = 0x9b05688c;
  digest[6] = 0x1f83d9ab;
  digest[7] = 0x5be0cd19;

  while (!reach_eof) {
    is.read(chunk, 64);
    int count = is.gcount();
    length += count * 8;

    if (count != 64) {
      reach_eof = true;
      chunk[count] = 0x80;
      count++;
      if (count > 56) {
        memset(chunk + count, 0, 64 - count);
        process();
        count = 0;
      }
      memset(chunk + count, 0, 56 - count);
      uint32_t high = swap_byte_order(length >> 32);
      uint32_t low = swap_byte_order(length & 0xffffffff);
      memcpy(chunk + 56, &high, sizeof(uint32_t));
      memcpy(chunk + 60, &low, sizeof(uint32_t));
      process();
    } else {
      process();
    }
  }

  for (int i = 0; i < 8; i++) {
    digest[i] = swap_byte_order(digest[i]);
  }
  unsigned char *bytes = reinterpret_cast<unsigned char *>(digest);
  for (int i = 0; i < 32; i++)
    os << std::hex << std::setfill('0') << std::setw(2) << (int)bytes[i];
  os << std::endl;
}

int main(int argc, char **argv) {
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      std::ifstream ifs(argv[i]);
      sha1(ifs, std::cout);
    }
  } else {
    sha1(std::cin, std::cout);
  }
  return 0;
}
