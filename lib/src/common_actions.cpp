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

#include <sudoku/common_actions.hpp>

#include <string>

#include <boost/format.hpp>

#include <sudoku/boolarray.hpp>
// #include <sudoku/technique.hpp>

namespace Sudoku {

  const std::string PLACE_DIGIT_NAME = "Place a digit";
  const std::string PLACE_DIGIT_DESCRIPTION
   = "Places the digit %1% at the cell (%2%,%3%)";

  PlaceDigit::PlaceDigit(int pos, int digit)
   : Action(PLACE_DIGIT_NAME,
            str(boost::format(PLACE_DIGIT_DESCRIPTION) % digit % (pos % 9 + 1) % (pos / 9 + 1))),
     pos(pos), digit(digit) { }

  bool PlaceDigit::do_action(Sudoku& sudoku) const {
    return sudoku.set_digit(pos, digit);
  }
  
  const std::string DELETE_PENCILMARK_NAME = "Delete a pencilmark";
  const std::string DELETE_PENCILMARK_DESCRIPTION
   = "Deletes the digit %1% pencilmark in the cells ";
  const std::string CELL_DESCRIPTION = "(%d,%d)";
  
  std::string get_delete_pencilmark_description(const Positions& places, int digit) {
    if (is_empty(places)) return std::string("No pencilmark will be deleted");
    
    std::string result(str(boost::format(DELETE_PENCILMARK_DESCRIPTION) % digit));
    result.reserve(result.length() + 7*places.size()); // 7 is length of "(x,y), "
    for (int i = 0; i < 81; ++i) {
      if (places[i]) {
        result.append(str(boost::format(CELL_DESCRIPTION) % (i % 9 + 1) % (i / 9 + 1)));
        result.append(", ");
      }
    }
    result.resize(result.size() - 2);
    return result;
  }
  
  DeletePencilMark::DeletePencilMark(const Positions& places, int digit)
   : Action(DELETE_PENCILMARK_NAME,
            get_delete_pencilmark_description(places, digit)),
            places(places), digit(digit) { }
  
  bool DeletePencilMark::do_action(Sudoku& sudoku) const {
    bool result = true;
    for (int i = 0; i < 81; ++i) {
      if (places[i]) {
        const bool temp_result = sudoku.set_pencilmark(i, digit, false);
        result = result || temp_result;
      }
    }
    return result;
  }

} // namespace Sudoku
