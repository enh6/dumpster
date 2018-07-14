#if 0
g++ -std=c++14 -Wall -O3 -o sha1 $0
exit
#endif

#include <cstdint>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>

uint32_t x[80], digest[5];

inline uint32_t swap_byte_order(uint32_t x) {
  return ((x << 24) & 0xff000000) | ((x << 8) & 0x00ff0000) |
         ((x >> 8) & 0x0000ff00) | ((x >> 24) & 0x000000ff);
}

void process() {
  uint32_t a = digest[0], b = digest[1], c = digest[2], d = digest[3],
           e = digest[4];

  for (int i = 0; i < 16; i++) {
    x[i] = swap_byte_order(x[i]);
  }
  for (int i = 16; i < 80; i++) {
    x[i] = (x[i - 3] ^ x[i - 8] ^ x[i - 14] ^ x[i - 16]);
    x[i] = (x[i] << 1) | (x[i] >> 31);
  }

  auto R = [](auto x, auto n) { return (x << n) | (x >> (32 - n)); };
  auto F = [](auto x, auto y, auto z) { return (x & y) | (~x & z); };
  auto G = [](auto x, auto y, auto z) { return x ^ y ^ z; };
  auto H = [](auto x, auto y, auto z) { return (x & y) | (x & z) | (y & z); };
  auto OP = [&](auto op, auto x, auto ac) {
    auto tmp = R(a, 5) + op(b, c, d) + e + x + (uint32_t)ac;
    e = d;
    d = c;
    c = R(b, 30);
    b = a;
    a = tmp;
  };

  for (int i = 0; i < 20; i++) {
    OP(F, x[i], 0x5a827999);
  }
  for (int i = 20; i < 40; i++) {
    OP(G, x[i], 0x6ed9eba1);
  }
  for (int i = 40; i < 60; i++) {
    OP(H, x[i], 0x8f1bbcdc);
  }
  for (int i = 60; i < 80; i++) {
    OP(G, x[i], 0xca62c1d6);
  }

  digest[0] += a;
  digest[1] += b;
  digest[2] += c;
  digest[3] += d;
  digest[4] += e;
}

void sha1(std::istream &is, std::ostream &os) {
  uint64_t length = 0;
  bool reach_eof = false;
  char *chunk = reinterpret_cast<char *>(x);
  digest[0] = 0x67452301;
  digest[1] = 0xefcdab89;
  digest[2] = 0x98badcfe;
  digest[3] = 0x10325476;
  digest[4] = 0xc3d2e1f0;

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

  for (int i = 0; i < 5; i++) {
    digest[i] = swap_byte_order(digest[i]);
  }
  unsigned char *bytes = reinterpret_cast<unsigned char *>(digest);
  for (int i = 0; i < 20; i++)
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
