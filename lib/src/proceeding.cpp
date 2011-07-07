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

#include <sudoku/proceeding.hpp>

// #include <set>
// #include <utility>

#include <sudoku/sudoku.hpp>

namespace Sudoku {

  void Proceeding::evaluate(Technique::Difficulty& max_difficulty, int& score) const {
    max_difficulty = Technique::EASY;
    score = 0;

    for (unsigned int i = 0; i < steps.size(); ++i) {
      const Step& step = steps[i];
      score += step.get_points();
      if (max_difficulty <= step.get_technique().get_difficulty()) {
        max_difficulty = step.get_technique().get_difficulty();
      }
    }
  }

  bool Proceeding::apply(Sudoku& sudoku) const {
    Sudoku temp(sudoku);
    for (unsigned int i = 0; i < steps.size(); ++i) {
      if (!steps[i].apply(temp)) {
        return false;
      }
    }
    sudoku = temp;
    return sudoku.is_finished();
  }

} // namespace Sudoku
