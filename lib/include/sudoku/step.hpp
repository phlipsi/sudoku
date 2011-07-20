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

#ifndef __STEP_HPP
#define __STEP_HPP

#include <string>

#include <sudoku/action.hpp>

namespace Sudoku {

  class Sudoku;
  class Technique;

  class Step {
  public:
    enum Difficulty { EASY = 1, MODERATE = 2, TOUGH = 3, HARD = 4, UNFAIR = 5 };

    Step() : technique(0), points(0) { }
    
    Step(Technique& technique,
         const std::string& vague_hint,
         const std::string& hint,
         Difficulty difficulty,
         const Actions& actions,
         int points)
      : technique(&technique),
        vague_hint(vague_hint),
        hint(hint),
        difficulty(difficulty),
        actions(actions),
        points(points) { }

    void inc_points(int increment) { points += increment; }

    Technique& get_technique() const { return *technique; }
    const std::string& get_vague_hint() const { return vague_hint; }
    const std::string& get_hint() const { return hint; }
    Difficulty get_difficulty() const { return difficulty; }
    int get_points() const { return points; }

    bool is_empty() const {
      return technique == 0;
    }

    bool apply(Sudoku& sudoku) const {
      return execute_actions(sudoku, actions);
    }
    
  private:
    Technique* technique;
    std::string vague_hint;
    std::string hint;
    Difficulty difficulty;
    Actions actions;
    int points;
  };

} // namespace Sudoku

#endif // __STEP_HPP
