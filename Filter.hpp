#ifndef __FILTER__
#define __FILTER__

#include <cstdint>
#include <string>
#include <vector>
#include <tuple>

#include "Hasher.hpp"
#include "Bithash.hpp"
#include "Util.hpp"

using std::string;
using std::vector;
using std::tuple;
using std::make_tuple;

class Filter
{
  public:
    Filter(uint64_t seed, uint32_t expected_items, uint32_t expected_item_length) :
      hasher(seed),
      prefix_set(bits_needed(expected_items, expected_item_length)),
      length_set(2*expected_item_length) {}

    void add(const std::string& word)
    {
      uint64_t hash = UINT64_C(0);
      for(size_t i = 0; i < word.length() ; i++)
      {
        hash = hasher.update(hash, word[i]);
        prefix_set.add(hash);
      }
      prefix_set.add(hash+1);
      length_set.add(word.length());
    }

   typedef tuple<size_t, size_t, uint64_t> result_t; 

   vector<result_t> match(const string& input)
   {
      vector<result_t> res;
      for (size_t i = 0 ; i < input.length() ; i++)
      {
        uint64_t hash = UINT64_C(0);
        for (size_t j = i ;  j < input.length() ; j++)
        {
          hash = hasher.update(hash, input[j]);
          if (!prefix_set.get(hash))
            break;

          const size_t prefix_len = j - i + 1;
          if (!length_set.get(prefix_len))
            continue;

          if (!prefix_set.get(hash+1))
            continue;
          
          res.push_back(make_tuple(i,j,hash));
        }
      }
      return res;
    }

  private:
    uint32_t bits_needed(uint32_t expected_items, uint32_t expected_size)
    {
      uint32_t bits = 2*next_power_of_two(expected_items*expected_size);
      return bits;
    }

  private:
    Hasher hasher;
    Bithash prefix_set;
    Bithash length_set;
};

#endif
