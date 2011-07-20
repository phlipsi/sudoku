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

#include <sudoku/backtracking.hpp>

#include <list>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

// #include <sudoku/action.hpp>
#include <sudoku/common_actions.hpp>
#include <sudoku/field.hpp>
// #include <sudoku/sudoku.hpp>

namespace Sudoku {

  Step BackTracking::do_try_technique(const Sudoku& sudoku) {
    Field f = sudoku.get_current_field();
    std::list<Field> solutions;
    const int number = f.solutions(2, solutions);
    if (number == 1) {
      for (int i = 0; i < 81; ++i) {
        if (f.get_digit(i) == 0) {
          const int digit = solutions.front().get_digit(i);
          Actions proposed_actions;
          proposed_actions.push_back(boost::shared_ptr<Action>(new PlaceDigit(i, digit)));
          const std::string vague_hint = boost::str(boost::format("Put digit %1% in the cell %2%:%3%") % digit % (get_row(i) + 1) % (get_col(i) + 1));
          const std::string hint = vague_hint;
          return Step(*this, vague_hint, hint, Step::UNFAIR, proposed_actions, 1200);
        }
      }
    }
    return Step();
  }

} // namespace Sudoku
