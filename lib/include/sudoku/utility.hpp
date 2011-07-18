#ifndef __UTILITY_HPP
#define __UTILITY_HPP

#include <cstdlib>

namespace Sudoku {

  template<typename InputIterator>
  InputIterator pick_randomly(InputIterator begin, InputIterator end) {
    InputIterator result = end;
    int so_far = 1;
    for (InputIterator it = begin; it != end; ++it) {
      if (rand() % so_far == 0) {
        result = it;
      }
    }
    return result;
  }

} // namespace Sudoku

#endif // __UTILITY_HPP
