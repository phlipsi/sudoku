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

#ifndef __COMMON_ACTIONS_HPP
#define __COMMON_ACTIONS_HPP

#include <sudoku/action.hpp>
#include <sudoku/positions.hpp>
#include <sudoku/sudoku.hpp>

namespace Sudoku {

  class PlaceDigit : public Action {
  private:
    int pos;
    int digit;
  public:
    PlaceDigit(int pos, int digit);
    
    virtual bool do_action(Sudoku& sudoku) const;
  };
  
  class DeletePencilMark : public Action {
  private:
    Positions places;
    int digit;
  public:
    DeletePencilMark(const Positions& places, int digit);
    
    virtual bool do_action(Sudoku& sudoku) const;
  };

} // namespace Sudoku

#endif // __COMMON_ACTIONS_HPP
