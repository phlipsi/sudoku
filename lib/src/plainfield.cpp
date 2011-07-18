#include <sudoku/plainfield.hpp>

#include <sudoku/boolarray.hpp>
#include <sudoku/pencilmarks.hpp>
#include <sudoku/positions.hpp>

namespace Sudoku {

  namespace {
  
    struct Data {
      boost::array<int, 81> field;
      int count;
      std::list< boost::array<int, 81> >& solutions;
    };

    void solutions_impl(Data& data, int next) {
      if (data.count <= 0) return;
      
      while (next < 81 && data.field[next] != 0) {
        ++next;
      }
      
      if (next >= 81) {
        data.solutions.push_back(data.field);
        --data.count;
        return;
      }
      
      Pencilmarks allowed;
      allowed.assign(true);
      for (int i = 0; i < 81; ++i) {
        if (PROPER_PEERS[next][i]) {
          const int d = data.field[i];
          if (d != 0) {
            allowed[d - 1] = false;
          }
        }
      }
      if (is_empty(allowed)) {
        return;
      }
      for (int i = 0; i < 9; ++i) {
        if (allowed[i]) {
          data.field[next] = i + 1;
          solutions_impl(data, next + 1);
          if (data.count <= 0) return;
        }
      }
      data.field[next] = 0;
    }
  }

  int solutions(const boost::array<int, 81>& plain_field, int max, std::list< boost::array<int, 81> >& sols) {
    Data data = { plain_field, max, sols };
    solutions_impl(data, 0);
    return max - data.count;
  }

  bool unique(const boost::array<int, 81>& plain_field) {
    std::list< boost::array<int, 81> > sols;
    return solutions(plain_field, 2, sols) == 1;
  }
  
} // namespace Sudoku
