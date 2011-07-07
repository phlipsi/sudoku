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

#include <sudoku/nakedsingle.hpp>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

// #include <sudoku/action.hpp>
#include <sudoku/boolarray.hpp>
#include <sudoku/common_actions.hpp>
#include <sudoku/pencilmarks.hpp>

namespace Sudoku {

  Step NakedSingle::do_try_technique(const Sudoku& sudoku) {
    for (int i = 0; i < 81; ++i) {
      if (sudoku.get_digit(i) == 0) {
        const Pencilmarks& p = sudoku.get_pencilmarks(i);
        if (is_sole(p)) {
          const int digit = first(p) + 1;
          Actions proposed_actions;
          boost::shared_ptr<Action> s(new PlaceDigit(i, digit));
          proposed_actions.push_back(s);
          const std::string vague_hint = boost::str(boost::format("Check digit %1%") % digit);
          const std::string hint = boost::str(boost::format("Digit %1% is the last remaining candidate in cell %2%:%3%") % digit % (get_row(i) + 1) % (get_col(i) + 1));
          const int points = 4;
          
          return Step(*this, vague_hint, hint, proposed_actions, points);
        }
      }
    }
    return Step();
  }

} // namespace Sudoku
