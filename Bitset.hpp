#ifndef __BITSET__
#define __BITSET__

#include <cstdint>

class Bitset
{
  public:
    Bitset(uint32_t size) : bits(alloc(bits_to_uint64(size)))
    {
    }

    ~Bitset()
    {
      if (bits)
      {
        delete bits;
        bits = NULL;
      }
    }

    void set(const uint32_t position)
    {
      const uint32_t i = position >> 6; // position / 64
      const uint32_t j = position & 63; // position % 64
      bits[i] |= (UINT64_C(1) << j);
    }

    inline bool test(const uint32_t position) const
    {
      const uint32_t i = position >> 6; // position / 64
      const uint32_t j = position & 63; // position % 64
      return (bits[i] >> j) & UINT64_C(1);
    }

  private:
    static uint32_t bits_to_uint64(uint32_t bits)
    {
      return (bits + 63) / 64; 
    } 

    static uint64_t* alloc(uint32_t size)
    {
      // TODO: sainty check @size
      uint64_t* array = new uint64_t[size];
      for (uint32_t i = 0 ; i < size ; i++)
      {
        array[i] = UINT64_C(0);
      }
      return array;
    }

  private:
    uint64_t *bits;
};

#endif
