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

#ifndef __SUDOKU_HPP
#define __SUDOKU_HPP

#include <sudoku/cell.hpp>
#include <sudoku/field.hpp>
#include <sudoku/pencilmarks.hpp>
#include <sudoku/positions.hpp>

namespace Sudoku {

  class Sudoku {
  public:
    Sudoku() : setup_mode(true) {
      clear();
    }

    Sudoku(const boost::array<int, 81>& sudoku) {
      assign(sudoku);
    }
    
    Sudoku(const std::string& sudoku) {
      assign(sudoku);
    }
    
    void clear() {
      setup_mode = true;
      setup_field.clear();
      field = setup_field;
    }
    
    void assign(const std::string& sudoku);
    void assign(const boost::array<int, 81>& sudoku);
    
    void setup();
    void start();
    
    const Field& get_current_field() const { return setup_mode ? setup_field : field; }
    
    const Cell& get(int i) const { return setup_mode ? setup_field[i] : field[i]; }
    const Cell& operator [] (int i) const { return get(i); }

    int get_digit(int pos) const { return get(pos).get_digit(); }
    bool get_pencilmark(int pos, int digit) const { return get(pos).get(digit); }

    bool set_digit(int pos, int digit);
    bool set_pencilmark(int pos, int digit, bool state);

    Positions get_not_set_sole_positions() const {
      return setup_mode ? setup_field.get_not_set_sole_positions() : field.get_not_set_sole_positions();
    }

    Positions get_not_fixed_digit_positions(int digit) const {
      return setup_mode ? setup_field.get_not_fixed_digit_positions(digit) : field.get_not_fixed_digit_positions(digit);
    }

    Positions get_open_positions() const {
      return setup_mode ? setup_field.get_open_positions() : field.get_open_positions();
    }

    const Pencilmarks& get_pencilmarks(int pos) const {
      return setup_mode ? setup_field.get_pencilmarks(pos) : field.get_pencilmarks(pos);
    }
    
    void restart_pencilmarks();
    
    bool is_finished() const { return setup_mode ? setup_field.is_finished() : field.is_finished(); }

    bool unique(int max_fails = -1) const { return setup_mode ? setup_field.unique(max_fails) : field.unique(max_fails); }
    
    int count_solutions(int max, int max_fails = -1) const {
      return setup_mode ? setup_field.count_solutions(max, max_fails) : field.count_solutions(max, max_fails);
    }
    
    enum Solutions { NONE = 0, UNIQUE = 1, MULTIPLE = 2 };
    Solutions solve();

    bool same_setup(const Sudoku& sudoku) const { return setup_field == sudoku.setup_field; }
    bool operator == (const Sudoku& sudoku) const {
      return setup_mode == sudoku.setup_mode && setup_field == sudoku.setup_field &&
        (setup_mode || field == sudoku.field);
    }

    bool check_symmetry(const Symmetry& symmetry) const {
      return setup_field.check_symmetry(symmetry);
    }

    void print(std::ostream& stream) const {
      if (setup_mode) {
        stream << setup_field;
      } else {
        stream << field;
      }
    }

  private:
    bool setup_mode;
    Field setup_field;
    Field field;
  };

  /*class Sudoku {
  public:
    Sudoku()
      : setup(), field(), fixed(setup.get_sole_positions()), setup_mode(true) { }
  
    Sudoku(const std::string& sudoku)
      : setup(sudoku), field(setup), fixed(setup.get_sole_positions()), setup_mode(false) { }
    
    void set_setup_mode(bool on);
    void set_cell(int pos, int digit);

  private:
    Field setup;
    Field field;
    Field::Positions fixed;
    bool setup_mode;
  };*/

} // namespace Sudoku

#endif // __SUDOKU_HPP
