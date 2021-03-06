// libsudoku
//
// Copyright 2011 Philipp Wähnert <phil.wnrt@googlemail.com>
//
// libsudoku is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.

#include <sudoku/field.hpp>
// #include <sudoku/boolarray.hpp>

namespace Sudoku {

  void Field::assign(const std::string& sudoku) {
    for (unsigned int i = 0; i < 81 && i < sudoku.size(); ++i) {
      const int value = sudoku[i] - 0x30;
      if ((value >= 0) || (value <= 9)) {
        cells[i] = Cell(value);
      }
    }
    for (unsigned int i = sudoku.size(); i < 81; ++i) {
      cells[i] = Cell();
    }
    restart_pencilmarks();
  }

  void Field::assign(const boost::array<int, 81>& f) {
    for (int i = 0; i < 81; ++i) {
      cells[i] = Cell(f[i]);
    }
    restart_pencilmarks();
  }

  void Field::restart_pencilmarks() {
    for (int i = 0; i < 81; ++i) {
      for (int j = 0; j < 81; ++j) {
        if (PROPER_PEERS[i][j]) {
          const int digit = cells[j].get_digit();
          if (digit != 0) {
            cells[i].set(digit, false);
          }
        }
      }
    }
  }

  bool Field::is_valid() const {
    boost::array<bool, 9> occured_row;
    boost::array<bool, 9> occured_col;
    boost::array<bool, 9> occured_box;
    
    for (int k = 0; k < 9; ++k) {
      occured_row.assign(false);
      occured_col.assign(false);
      occured_box.assign(false);
      
      for (int i = 0; i < 81; ++i) {
        const int d = cells[i].get_digit();
        if (d != 0) {
          if (ROWS[k][i]) {
            if (occured_row[d - 1]) {
              return false;
            }
            occured_row[d - 1] = true;
          }
          if (COLS[k][i]) {
            if (occured_col[d - 1]) {
              return false;
            }
            occured_col[d - 1] = true;
          }
          if (BOXES[k][i]) {
            if (occured_box[d - 1]) {
              return false;
            }
            occured_box[d - 1] = true;
          }
        }
      }
    }
    return true;
  }
  
  bool Field::is_finished() const {
    boost::array<bool, 9> occured_row;
    boost::array<bool, 9> occured_col;
    boost::array<bool, 9> occured_box;
    
    for (int k = 0; k < 9; ++k) {
      occured_row.assign(false);
      occured_col.assign(false);
      occured_box.assign(false);
      
      for (int i = 0; i < 81; ++i) {
        const int d = cells[i].get_digit();
        if (d != 0) {
          if (ROWS[k][i]) {
            if (occured_row[d - 1]) {
              return false;
            }
            occured_row[d - 1] = true;
          }
          if (COLS[k][i]) {
            if (occured_col[d - 1]) {
              return false;
            }
            occured_col[d - 1] = true;
          }
          if (BOXES[k][i]) {
            if (occured_box[d - 1]) {
              return false;
            }
            occured_box[d - 1] = true;
          }
        } else {
          return false;
        }
      }
    }
    return true;
  }

  bool Field::is_allowed(int pos, int digit) const {
    bool result = true;
    for (int i = 0; i < 81; ++i) {
      if (PROPER_PEERS[pos][i] && cells[i].get_digit() == digit) {
        result = false;
        break;
      }
    }
    return result;
  }
  
  bool Field::set_digit(int pos, int digit) {
    const int old = cells[pos].get_digit();
    if (old == digit) return true;
    if (digit != 0) {
      if (cells[pos].is_allowed(digit)) {
        cells[pos].set_to_digit(digit);
        for (int i = 0; i < 81; ++i) {
          if (PROPER_PEERS[pos][i]) {
            cells[i].set(digit, false);
          }
        }
      } else {
        return false;
      }
    } else {
      cells[pos].clear();
      for (int i = 0; i < 81; ++i) {
        if (PROPER_PEERS[pos][i]) {
          const int d = cells[i].get_digit();
          if (d != 0) {
            cells[pos].set(d, false);
          }
        }
      }
    }
    if (old != 0) {
      for (int i = 0; i < 81; ++i) {
        if (PROPER_PEERS[pos][i] && !cells[pos].is_fixed()) {
          if (is_allowed(i, old)) {
            // until now the digit wasn't allowed due to our 
            // cell so we only have to consider the case where
            // the peer cell allows the digit
            cells[i].set(old, true);
          }
          // bool allowed = true;
          // for (int j = 0; j < 81; ++j) {
          //   if (PROPER_PEERS[i][j]) {
          //     const int d = cells[j].get_digit();
          //     if (d == digit) {
          //       allowed = false;
          //     }
          //   }
          // }
          // cells[i].set(digit, allowed);
        }
      }
    }
    return true;
  }

  void Field::solutions_impl(boost::array<int, 81>& f, int next, int max, int& count, int max_fails, int& fails, std::list<Field>& sols) const {
    if (count >= max || (max_fails > 0 && fails >= max_fails)) return;
    
    while (next < 81 && f[next] != 0) {
      ++next;
    }
    
    if (next >= 81) {
      sols.push_back(Field(f));
      ++count;
      return;
    }
    
    Pencilmarks allowed = cells[next].get();
    // boost::array<bool, 9> allowed;
    // allowed.assign(true);
    for (int i = 0; i < 81; ++i) {
      if (PROPER_PEERS[next][i]) {
        const int d = f[i];
        if (d != 0) {
          allowed[d - 1] = false;
        }
      }
    }
    if (is_empty(allowed)) {
      ++fails;
      return;
    }
    for (int i = 0; i < 9; ++i) {
      if (allowed[i]) {
        f[next] = i + 1;
        solutions_impl(f, next + 1, max, count, max_fails, fails, sols);
        if (count >= max) return;
      }
    }
    f[next] = 0;
  }

  int Field::solutions(int max, std::list<Field>& sols, int max_fails) const {
    boost::array<int, 81> f;
    for (int i = 0; i < 81; i++) {
      f[i] = cells[i].get_digit();
    }
    for (int digit = 1; digit <= 9; ++digit) {
      const Positions p = get_not_fixed_digit_positions(digit);
      for (int i = 0; i < 9; ++i) {
        const Positions row = and_op(ROWS[i], p);
        if (is_sole(row)) {
          f[first(row)] = digit;
        }
        const Positions col = and_op(COLS[i], p);
        if (is_sole(col)) {
          f[first(col)] = digit;
        }
        const Positions box = and_op(BOXES[i], p);
        if (is_sole(box)) {
          f[first(box)] = digit;
        }
      }
    }
    int count = 0;
    int fails = 0;
    solutions_impl(f, 0, max, count, max_fails, fails, sols);
    return count;
  }

  bool Field::set_pencilmark(int pos, int digit, bool state) {
    if (!state) {
      cells[pos].set(digit, false);
      // if (cells[pos].get(digit)) {
      //   cells[pos].set(digit, false);
      // }
      return true;
    } else {
      if (is_allowed(pos, digit)) {
        cells[pos].set(digit, true);
        return true;
      } else {
        return false;
      }
    }
  }
    
} // namespace Sudoku
