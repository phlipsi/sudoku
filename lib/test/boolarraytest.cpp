#include <cstdlib>
#include <cassert>

#include <boost/array.hpp>

#include <sudoku/boolarray.hpp>

using namespace Sudoku;

const int N = 100;

int main() {
  boost::array<bool, N> a;
  int c = 0;
  for (int i = 0; i < N; ++i) {
    a[i] = rand() < RAND_MAX / 2;
    if (a[i]) ++c;
  }
  const int c2 = count(a);
  
  assert(c2 == c);
  assert(count(a) == c);
  assert(!(count(a) == c + 1));
  assert(!(count(a) == c - 1));

  assert(count(a) != c + 1);
  assert(count(a) != c - 1);
  assert(!(count(a) != c));
  
  assert(count(a) < c + 1);
  assert(!(count(a) < c));
  
  assert(count(a) <= c);
  assert(count(a) <= c + 1);
  assert(!(count(a) <= c - 1));
 
  assert(count(a) > c - 1);
  assert(!(count(a) > c));

  assert(count(a) >= c);
  assert(count(a) >= c - 1);
  assert(!(count(a) >= c + 1));
  
  return 0;
}
