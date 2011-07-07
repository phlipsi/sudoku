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

#ifndef __CELL_HPP
#define __CELL_HPP

#include <boost/array.hpp>

#include "boolarray.hpp"
#include "pencilmarks.hpp"

namespace Sudoku {

  class Cell {
  public:
    Cell() : digit(0), count(9) {
      // set_all_pencilmarks(true);
      pencilmarks.assign(true);
    }
    
    explicit Cell(int digit) : digit(digit), count(digit != 0 ? 1 : 9) {
      set_to_digit(digit);
    }
    
    // marks = "138" or marks = "813" means: 1, 3 and 8 are allowed
    explicit Cell(const std::string& marks) 
      : digit(0), count(0)
    {
      pencilmarks.assign(false);
      for (unsigned int i = 0; i < 9 && i < marks.size(); ++i) {
        const int m = marks[i] - 0x31;
        if (m >= 0 && m < 9) {
          pencilmarks[m] = true;
          ++count;
        }
      }
    }
    
    void set_to_digit(int new_digit) {
      digit = new_digit;
      if (new_digit != 0) {
        count = 1;
        pencilmarks.assign(false);
        pencilmarks[new_digit - 1] = true;
      } else {
        count = 9;
        pencilmarks.assign(true);
      }
    }
    
    int get_digit() const {
      return digit;
    }
    
    bool is_open() const {
      return count > 1;
      // return digit == 0 && is_open(pencilmarks);
    }
    
    bool is_sole() const {
      return count == 1;
      // return digit != 0 || is_sole(pencilmarks);
    }
    
    bool is_allowed(int digit) const { return pencilmarks[digit - 1]; }

    bool is_fixed() const { return digit != 0; }

    bool is_empty() const {
      return count == 0;
      // return digit == 0 && is_empty(pencilmarks);
    }
    
    int get_count() const { return count; }
    
    /*void test() const {
      if (digit == 0) {
        assert(is_empty(pencilmarks) || is_open(pencilmarks));
        assert(!is_sole(pencilmarks));
      } else {
        assert(count == 1);
        assert(!is_empty(pencilmarks));
        assert(!is_open(pencilmarks));
        assert(is_sole(pencilmarks));
      }      
    }*/
    
    // bool operator [] (int i) const { return pencilmarks[i]; }
    bool get(int digit) const { return pencilmarks[digit - 1]; }
    const Pencilmarks& get() const { return pencilmarks; }
    
    void set(int digit, bool state) {
      const bool old = pencilmarks[digit - 1];
      if (old != state) {
        pencilmarks[digit - 1] = state;
        if (state) {
          ++count;
        } else {
          --count;
        }
      }
    }
    
    void set(const Pencilmarks& p) {
      pencilmarks = p;
      count = 0;
      for (int i = 0; i < 9; ++i) {
        if (pencilmarks[i]) ++count;
      }
    }
    
    void clear() {
      digit = 0;
      count = 9;
      pencilmarks.assign(true);
    }
        
    bool operator == (const Cell& c) const {
      return digit == c.digit && count == c.count && pencilmarks == c.pencilmarks;
    }
      
  private:
    int digit;
    int count;
    Pencilmarks pencilmarks;
  };

} // namespace Sudoku

#endif // __CELL_HPP
