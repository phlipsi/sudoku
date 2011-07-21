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

#include <sudoku/sudoku.hpp>

namespace Sudoku {

  void Sudoku::assign(const std::string& sudoku) {
    setup_mode = false;
    setup_field.assign(sudoku);
    field = setup_field;
  }

  void Sudoku::assign(const boost::array<int, 81>& sudoku) {
    setup_mode = false;
    setup_field.assign(sudoku);
    field = setup_field;
  }

  void Sudoku::restart_pencilmarks() {
    if (setup_mode) {
      setup_field.restart_pencilmarks();
    } else {
      field.restart_pencilmarks();
    }
  }

  void Sudoku::setup() {
    setup_mode = true;
  }
  
  void Sudoku::start() {
    setup_mode = false;
    field = setup_field;
  }

  bool Sudoku::set_digit(int pos, int digit) {
    if (setup_mode) {
      return setup_field.set_digit(pos, digit);
    } else {
      return setup_field.get_digit(pos) == 0 && field.set_digit(pos, digit);
    }
  }
  
  bool Sudoku::set_pencilmark(int pos, int digit, bool state) {
    if (setup_mode) {
      return setup_field.set_pencilmark(pos, digit, state);
    } else {
      return (!state || setup_field.get_pencilmark(pos, digit)) && field.set_pencilmark(pos, digit, state);
    }
  }
  
  /*bool Sudoku::set_cell(int pos, int digit) {
    if (setup_mode) {
      return setup.set_digit(pos, digit);
    } else {
      if (setup[pos][digit - 1] && field.set_digit(pos, digit)) {
        fixed[pos] = digit != 0;
        return true;
      } else {
        return false;
      }
    }
  }*/

  Sudoku::Solutions Sudoku::solve() {
    Field& f = setup_mode ? setup_field : field;
    std::list<Field> solutions;
    const int result = f.solutions(2, solutions);
    if (result == 0) {
      return NONE;
    } else if (result == 1) {
      f = solutions.front();
      return UNIQUE;
    } else if (result > 1) {
      return MULTIPLE;
    }
    return NONE;
  }
  
}
