
#include <iostream>
#include <cstdint>
#include <string>
#include <fstream>

#include "Filter.hpp"

using namespace std;

static void add_lines_from_file(Filter& filter, const string& path)
{
  ifstream infile(path);
  string line;
  while (getline(infile, line))
  {
    if ((line.length() >= 4) && (line.length() < 22))
    {
      filter.add(line);
    }
  }
}

string slice(const string& word, size_t i, size_t j)
{
  return string(word.begin() + i, word.begin() + j + 1);
}

void print_possible_matches(Filter& filter, const string& word)
{
 size_t match_start;
 size_t match_end;
 uint64_t match_hash;

 auto res = filter.match(word);
 for (auto i = res.begin() ; i != res.end() ; i++)
 {
     tie(match_start,match_end,match_hash) = *i;
     cout << "possible match! hash: " << match_hash <<  " match: [" << slice(word,match_start, match_end) << "]" << endl;
 }
}

int main(int argc, char *argv[])
{
  uint32_t expected_items = 230 * 1000;
  uint32_t expected_size = 10;
  uint64_t random_seed = UINT64_C(1);
  Filter filter(random_seed, expected_items, expected_size);

  add_lines_from_file(filter, "/usr/share/dict/words");
  print_possible_matches(filter, "http://southpark.cc.com/full-episodes/s20e02-skank-hunt#source=2b6c5ab4-d717-4e84-9143-918793a3b636:63a32034-1ea6-492d-b95b-9433e3f62f8d&position=1&sort=airdate");
}
