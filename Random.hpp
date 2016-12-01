#ifndef __RANDOM__
#define __RANDOM__

#include <cstdint>

class Random
{
  public:
    Random(uint64_t seed) : s0(0x8a5cd789635d2dff), s1(seed)
    {
    }

    uint64_t next_uint64()
    {
      // xorshift128plus random number generator.
      uint64_t x = s0;
      uint64_t const y = s1;
      s0 = y;
      x ^= x << 23;
      s1 = x ^ y ^ (x >> 17) ^ (y >> 26);
      return s1 + y;

    }

  private:
    uint64_t s0;
    uint64_t s1;
};

#endif
