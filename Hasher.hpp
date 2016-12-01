#ifndef __HASHER__
#define __HASHER__

#include <cstdint>
#include <string>

#include "Random.hpp"

class Hasher
{
  public:
    Hasher(uint64_t seed)
    {
      Random random(seed);
      for (int i = 0 ; i < 256 ; i++)
      {
        byte_hash[i] = random.next_uint64();
      }
    }

    inline uint64_t hash(const char what)
    {
      return byte_hash[what & 0xFF];
    }

    inline uint64_t update(const uint64_t hash, const char what)
    {
     uint64_t result = (hash << 1) | (hash >> 63);
     return result ^ byte_hash[what & 0xff];
    }

  private:
    uint64_t byte_hash[256];
};

#endif
