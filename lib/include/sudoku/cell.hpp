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

#include <sudoku/boolarray.hpp>
#include <sudoku/pencilmarks.hpp>
#include <sudoku/property.hpp>

namespace Sudoku {

  class Cell {
  public:
    Cell() : m_digit(0), m_count(9) {
      // set_all_pencilmarks(true);
      m_pencilmarks.assign(true);
    }
    
    explicit Cell(int digit) : m_digit(digit), m_count(digit != 0 ? 1 : 9) {
      set_to_digit(digit);
    }
    
    // marks = "138" or marks = "813" means: 1, 3 and 8 are allowed
    explicit Cell(const std::string& marks) 
      : m_digit(0), m_count(0)
    {
      m_pencilmarks.assign(false);
      for (unsigned int i = 0; i < 9 && i < marks.size(); ++i) {
        const int m = marks[i] - 0x31;
        if (m >= 0 && m < 9) {
          m_pencilmarks[m] = true;
          ++m_count;
        }
      }
    }
    
    void set_to_digit(int new_digit) {
      m_digit = new_digit;
      if (new_digit != 0) {
        m_count = 1;
        m_pencilmarks.assign(false);
        m_pencilmarks[new_digit - 1] = true;
      } else {
        m_count = 9;
        m_pencilmarks.assign(true);
      }
    }
    
    int get_digit() const {
      return m_digit;
    }
    
    bool is_open() const {
      return m_count > 1;
      // return m_digit == 0 && is_open(m_pencilmarks);
    }
    
    bool is_sole() const {
      return m_count == 1;
      // return m_digit != 0 || is_sole(m_pencilmarks);
    }
    
    bool is_allowed(int digit) const { return m_pencilmarks[digit - 1]; }

    bool is_fixed() const { return m_digit != 0; }

    bool is_empty() const {
      return m_count == 0;
      // return m_digit == 0 && is_empty(m_pencilmarks);
    }
    
    int get_count() const { return m_count; }
    
    /*void test() const {
      if (m_digit == 0) {
        assert(is_empty(m_pencilmarks) || is_open(m_pencilmarks));
        assert(!is_sole(m_pencilmarks));
      } else {
        assert(m_count == 1);
        assert(!is_empty(m_pencilmarks));
        assert(!is_open(m_pencilmarks));
        assert(is_sole(m_pencilmarks));
      }      
    }*/
    
    // bool operator [] (int i) const { return m_pencilmarks[i]; }
    bool get(int digit) const { return m_pencilmarks[digit - 1]; }
    const Pencilmarks& get() const { return m_pencilmarks; }
    
    void set(int digit, bool state) {
      const bool old = m_pencilmarks[digit - 1];
      if (old != state) {
        m_pencilmarks[digit - 1] = state;
        if (state) {
          ++m_count;
        } else {
          --m_count;
        }
      }
    }
    
    void set(const Pencilmarks& p) {
      m_pencilmarks = p;
      m_count = 0;
      for (int i = 0; i < 9; ++i) {
        if (m_pencilmarks[i]) ++m_count;
      }
    }
    
    void clear() {
      m_digit = 0;
      m_count = 9;
      m_pencilmarks.assign(true);
    }
        
    bool operator == (const Cell& c) const {
      return m_digit == c.m_digit && m_count == c.m_count && m_pencilmarks == c.m_pencilmarks;
    }

    typedef Properties::MemberProperty<int, Cell> Digit;
    typedef Properties::MemberProperty<int, Cell> Count;
    
    class Pencilmark {
    public:
      typedef Cell Type;
      Pencilmark(int digit) : digit(digit) { }
      
      int operator () (const Type& cell) { return cell.get(digit); }
    private:
      int digit;
    };
    
    
    static Digit digit() { return Digit(&Cell::get_digit); }
    static Count count() { return Count(&Cell::get_count); }
    static Pencilmark pencilmark(int digit) { return Pencilmark(digit); }

  private:
    int m_digit;
    int m_count;
    Pencilmarks m_pencilmarks;
  };

} // namespace Sudoku

#endif // __CELL_HPP
