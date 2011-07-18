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

#include <sudoku/solver.hpp>

#include <sudoku/action.hpp>
#include <sudoku/proceeding.hpp>
#include <sudoku/step.hpp>
#include <sudoku/sudoku.hpp>

namespace Sudoku {

  Proceeding Solver::solve(const Sudoku& sudoku, bool assume_uniqueness) {
    Proceeding proceeding;
    proceeding.clear_steps();
    list.reset_techniques();
    Sudoku temp = sudoku;
    
    bool success = true;
    while (!temp.is_finished() && success) {
      success = false;
      for (iterator i = begin(); i != end(); ++i) {
        if (assume_uniqueness || !i->does_require_uniqueness()) {
          Step step = i->try_technique(temp);
          if (!step.is_empty()) {
            if (step.apply(temp)) {
              success = true;
              proceeding.append_step(step);
              break;
            }
          }
        }
      }
    }
    
    proceeding.set_solved(success);
    return proceeding;
  }

} // namespace Sudoku
