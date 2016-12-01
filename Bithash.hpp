#ifndef __BITHASH__
#define __BITHASH__

#include <cstdint>
#include "Util.hpp"

class Bithash
{
  public:
    Bithash(uint32_t n) : bits(init(size(n))), mask(size(n) - 1)
    {
    }

    ~Bithash()
    {
      if (bits)
      {
        delete bits;
        bits = NULL;
      }
    }

    void add(const uint64_t key)
    {
      const uint32_t pos = position(key, mask);
      const uint32_t i = pos >> 6; // position / 64
      const uint32_t j = pos & 63; // position % 64
      bits[i] |= (UINT64_C(1) << j);
    }

    inline bool get(const uint64_t key) const
    {
      const uint32_t pos = position(key, mask);
      const uint32_t i = pos >> 6; // position / 64
      const uint32_t j = pos & 63; // position % 64
      return (bits[i] >> j) & UINT64_C(1);
    }

  private:
    static inline uint32_t position(uint64_t key, const uint32_t mask) 
    {
      key ^= key >> 33;
      key *= UINT64_C(0xff51afd7ed558ccd);
      key ^= key >> 33;
      key *= UINT64_C(0xc4ceb9fe1a85ec53);
      key ^= key >> 33;
      return static_cast<uint32_t>(key & mask);
    }

    static uint32_t size(uint32_t bits)
    {
      return next_power_of_two(bits);
    }

    static uint64_t* init(uint32_t size)
    {
      // TODO: sainty check @size
      const uint32_t n = size / 64;
      uint64_t* array = new uint64_t[n];
      for (uint32_t i = 0 ; i < n ; i++)
      {
        array[i] = UINT64_C(0);
      }
      return array;
    }

  private:
    uint64_t *bits;
    uint32_t mask;
};

#endif
