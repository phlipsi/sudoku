#include <sudoku/generator.hpp>

#include <vector>
#include <algorithm>

#include <boost/array.hpp>

#include <sudoku/sudoku.hpp>

namespace Sudoku {

  namespace {
    
    bool generate_full_impl(int last, int& misses, boost::array<int, 81>& field) {
      if (last == 80) {
        return true;
      }
      
      const int next = last + 1;
      boost::array<bool, 9> allowed;
      allowed.assign(true);
      for (int i = 0; i < 81; ++i) {
        if (PROPER_PEERS[next][i]) {
          const int digit = field[i];
          if (digit != 0) {
            allowed[digit - 1] = false;
          }
        }
      }
      std::vector<int> allowed_digits;
      allowed_digits.reserve(9);
      for (int d = 0; d < 9; ++d) {
        if (allowed[d]) {
          allowed_digits.push_back(d + 1);
        }
      }
      if (allowed_digits.empty()) ++misses;
      std::random_shuffle(allowed_digits.begin(), allowed_digits.end());
      for (unsigned int i = 0; i < allowed_digits.size(); ++i) {
        field[next] = allowed_digits[i];
        if (generate_full_impl(next, misses, field)) {
          return true;
        }
      }
      field[next] = 0;
      return false;
    }
    
  }

  Sudoku generate_full(int& misses) {
    boost::array<int, 81> field;
    field.assign(0);
    misses = 0;
    if (generate_full_impl(-1, misses, field)) {
      return Sudoku(field);
    } else {
      return Sudoku();
    }
  }

} // namespace Sudoku
