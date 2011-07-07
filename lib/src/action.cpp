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

#include <sudoku/action.hpp>

namespace Sudoku {

  bool execute_actions(Sudoku& sudoku, const Actions& actions) {
    for (Actions::const_iterator i = actions.begin(); i != actions.end(); ++i) {
      if (!(*i)->do_action(sudoku)) {
        return false;
      }
    }
    return true;
  }

} // namespace Sudoku
