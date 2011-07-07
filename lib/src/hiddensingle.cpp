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

#include <sudoku/hiddensingle.hpp>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <sudoku/boolarray.hpp>
#include <sudoku/common_actions.hpp>
#include <sudoku/positions.hpp>

namespace Sudoku {

  Step HiddenSingleRow::do_try_technique(const Sudoku& sudoku) {
    for (int digit = 1; digit <= 9; ++digit) {
      const Positions p = sudoku.get_not_fixed_digit_positions(digit);
      for (int i = 0; i < 9; ++i) {
        int where = -1;
        if (is_sole(p, ROWS[i], where)) {
          const std::string vague_hint = "There's a hidden single in one row";
          const std::string hint = boost::str(boost::format("Hidden single for digit %1% in row %2% ") % digit % (i + 1));
          Actions proposed_actions;
          proposed_actions.push_back(boost::shared_ptr<Action>(new PlaceDigit(where, digit)));
          
          int points = 0;
          int other_where = -1;
          if (is_sole(p, COLS[get_col(where)], other_where) ||
              is_sole(p, BOXES[get_box(where)], other_where)) {
            points = 8;
          } else {
            points = 14;
          }
          
          return Step(*this, vague_hint, hint, proposed_actions, points);
        }
      }
    }
    return Step();
  }

  Step HiddenSingleColumn::do_try_technique(const Sudoku& sudoku) {
    for (int digit = 1; digit <= 9; ++digit) {
      const Positions p = sudoku.get_not_fixed_digit_positions(digit);
      for (int i = 0; i < 9; ++i) {
        int where = -1;
        if (is_sole(p, COLS[i], where)) {
          const std::string vague_hint = "There's a hidden single in one column";
          const std::string hint = boost::str(boost::format("Hidden single for digit %1% in column %2% ") % digit % (i + 1));
          Actions proposed_actions;
          proposed_actions.push_back(boost::shared_ptr<Action>(new PlaceDigit(where, digit)));

          int points = 0;
          int other_where = -1;
          if (is_sole(p, ROWS[get_col(where)], other_where) ||
              is_sole(p, BOXES[get_box(where)], other_where)) {
            points = 8;
          } else {
            points = 20;
          }

          return Step(*this, vague_hint, hint, proposed_actions, points);
        }
      }
    }
    return Step();
  }

  Step HiddenSingleBox::do_try_technique(const Sudoku& sudoku) {
    for (int digit = 1; digit <= 9; ++digit) {
      const Positions p = sudoku.get_not_fixed_digit_positions(digit);
      for (int i = 0; i < 9; ++i) {
        int where = -1;
        if (is_sole(p, BOXES[i], where)) {
          const std::string vague_hint = "There's a hidden single in one box";
          const std::string hint = boost::str(boost::format("Hidden single for digit %1% in box %2% ") % digit % (i + 1));
          Actions proposed_actions;
          proposed_actions.push_back(boost::shared_ptr<Action>(new PlaceDigit(where, digit)));

          int points;
          int other_where = -1;
          if (is_sole(p, COLS[get_col(where)], other_where) ||
              is_sole(p, ROWS[get_box(where)], other_where)) {
            points = 8;
          } else {
            points = 10;
          }

          return Step(*this, vague_hint, hint, proposed_actions, points);
        }
      }
    }
    return Step();
  }

} // namespace Sudoku
