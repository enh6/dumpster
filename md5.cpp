#if 0
g++ -std=c++14 -Wall -O3 -o md5 $0
exit
#endif

#include <cstdint>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>

uint32_t x[16], digest[4];

void process() {
  uint32_t a = digest[0], b = digest[1], c = digest[2], d = digest[3];

  auto F = [](auto x, auto y, auto z) { return (x & y) | (~x & z); };
  auto G = [](auto x, auto y, auto z) { return (x & z) | (y & ~z); };
  auto H = [](auto x, auto y, auto z) { return x ^ y ^ z; };
  auto I = [](auto x, auto y, auto z) { return y ^ (x | ~z); };
  auto OP = [](auto op, auto &a, auto b, auto c, auto d, auto x, auto s,
               auto ac) {
    a += op(b, c, d) + x + (uint32_t)ac;
    a = (a << s) | (a >> (32 - s));
    a += b;
  };

  /* Round 1 */
  OP(F, a, b, c, d, x[0], 7, 0xd76aa478);
  OP(F, d, a, b, c, x[1], 12, 0xe8c7b756);
  OP(F, c, d, a, b, x[2], 17, 0x242070db);
  OP(F, b, c, d, a, x[3], 22, 0xc1bdceee);
  OP(F, a, b, c, d, x[4], 7, 0xf57c0faf);
  OP(F, d, a, b, c, x[5], 12, 0x4787c62a);
  OP(F, c, d, a, b, x[6], 17, 0xa8304613);
  OP(F, b, c, d, a, x[7], 22, 0xfd469501);
  OP(F, a, b, c, d, x[8], 7, 0x698098d8);
  OP(F, d, a, b, c, x[9], 12, 0x8b44f7af);
  OP(F, c, d, a, b, x[10], 17, 0xffff5bb1);
  OP(F, b, c, d, a, x[11], 22, 0x895cd7be);
  OP(F, a, b, c, d, x[12], 7, 0x6b901122);
  OP(F, d, a, b, c, x[13], 12, 0xfd987193);
  OP(F, c, d, a, b, x[14], 17, 0xa679438e);
  OP(F, b, c, d, a, x[15], 22, 0x49b40821);

  /* Round 2 */
  OP(G, a, b, c, d, x[1], 5, 0xf61e2562);
  OP(G, d, a, b, c, x[6], 9, 0xc040b340);
  OP(G, c, d, a, b, x[11], 14, 0x265e5a51);
  OP(G, b, c, d, a, x[0], 20, 0xe9b6c7aa);
  OP(G, a, b, c, d, x[5], 5, 0xd62f105d);
  OP(G, d, a, b, c, x[10], 9, 0x02441453);
  OP(G, c, d, a, b, x[15], 14, 0xd8a1e681);
  OP(G, b, c, d, a, x[4], 20, 0xe7d3fbc8);
  OP(G, a, b, c, d, x[9], 5, 0x21e1cde6);
  OP(G, d, a, b, c, x[14], 9, 0xc33707d6);
  OP(G, c, d, a, b, x[3], 14, 0xf4d50d87);
  OP(G, b, c, d, a, x[8], 20, 0x455a14ed);
  OP(G, a, b, c, d, x[13], 5, 0xa9e3e905);
  OP(G, d, a, b, c, x[2], 9, 0xfcefa3f8);
  OP(G, c, d, a, b, x[7], 14, 0x676f02d9);
  OP(G, b, c, d, a, x[12], 20, 0x8d2a4c8a);

  /* Round 3 */
  OP(H, a, b, c, d, x[5], 4, 0xfffa3942);
  OP(H, d, a, b, c, x[8], 11, 0x8771f681);
  OP(H, c, d, a, b, x[11], 16, 0x6d9d6122);
  OP(H, b, c, d, a, x[14], 23, 0xfde5380c);
  OP(H, a, b, c, d, x[1], 4, 0xa4beea44);
  OP(H, d, a, b, c, x[4], 11, 0x4bdecfa9);
  OP(H, c, d, a, b, x[7], 16, 0xf6bb4b60);
  OP(H, b, c, d, a, x[10], 23, 0xbebfbc70);
  OP(H, a, b, c, d, x[13], 4, 0x289b7ec6);
  OP(H, d, a, b, c, x[0], 11, 0xeaa127fa);
  OP(H, c, d, a, b, x[3], 16, 0xd4ef3085);
  OP(H, b, c, d, a, x[6], 23, 0x04881d05);
  OP(H, a, b, c, d, x[9], 4, 0xd9d4d039);
  OP(H, d, a, b, c, x[12], 11, 0xe6db99e5);
  OP(H, c, d, a, b, x[15], 16, 0x1fa27cf8);
  OP(H, b, c, d, a, x[2], 23, 0xc4ac5665);

  /* Round 4 */
  OP(I, a, b, c, d, x[0], 6, 0xf4292244);
  OP(I, d, a, b, c, x[7], 10, 0x432aff97);
  OP(I, c, d, a, b, x[14], 15, 0xab9423a7);
  OP(I, b, c, d, a, x[5], 21, 0xfc93a039);
  OP(I, a, b, c, d, x[12], 6, 0x655b59c3);
  OP(I, d, a, b, c, x[3], 10, 0x8f0ccc92);
  OP(I, c, d, a, b, x[10], 15, 0xffeff47d);
  OP(I, b, c, d, a, x[1], 21, 0x85845dd1);
  OP(I, a, b, c, d, x[8], 6, 0x6fa87e4f);
  OP(I, d, a, b, c, x[15], 10, 0xfe2ce6e0);
  OP(I, c, d, a, b, x[6], 15, 0xa3014314);
  OP(I, b, c, d, a, x[13], 21, 0x4e0811a1);
  OP(I, a, b, c, d, x[4], 6, 0xf7537e82);
  OP(I, d, a, b, c, x[11], 10, 0xbd3af235);
  OP(I, c, d, a, b, x[2], 15, 0x2ad7d2bb);
  OP(I, b, c, d, a, x[9], 21, 0xeb86d391);

  digest[0] += a;
  digest[1] += b;
  digest[2] += c;
  digest[3] += d;
}

void md5(std::istream &is, std::ostream &os) {
  uint64_t length = 0;
  bool reach_eof = false;
  char *chunk = reinterpret_cast<char *>(x);
  digest[0] = 0x67452301;
  digest[1] = 0xefcdab89;
  digest[2] = 0x98badcfe;
  digest[3] = 0x10325476;

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
      memcpy(chunk + 56, &length, sizeof(length));
      process();
    } else {
      process();
    }
  }

  unsigned char *bytes = reinterpret_cast<unsigned char *>(digest);
  for (int i = 0; i < 16; i++)
    os << std::hex << std::setfill('0') << std::setw(2) << (int)bytes[i];
  os << std::endl;
}

int main(int argc, char **argv) {
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      std::ifstream ifs(argv[i]);
      md5(ifs, std::cout);
    }
  } else {
    md5(std::cin, std::cout);
  }
  return 0;
}
