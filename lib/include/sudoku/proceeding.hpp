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

#ifndef __PROCEEDING_HPP
#define __PROCEEDING_HPP

#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>

#include <sudoku/action.hpp>
#include <sudoku/step.hpp>
#include <sudoku/technique.hpp>

namespace Sudoku {

  class Sudoku;

  class Proceeding {
  public:
    /*struct Step {
      Step(const Technique& technique,
           Actions actions,
           const std::string& vague_hint,
           const std::string& hint)
        : technique(&technique), actions(actions), vague_hint(vague_hint), hint(hint) { }

      const Technique* technique;
      Actions actions;
      std::string vague_hint;
      std::string hint;
    };*/

    Proceeding() { steps.reserve(81); }
  
    void append_step(const Step& step) {
      steps.push_back(step);
    }
    
    int count_steps() const { return steps.size(); }
    const Step& get_step(int index) const { return steps[index]; }

    void evaluate(Technique::Difficulty& max_difficulty, int& score) const;
    bool apply(Sudoku& sudoku) const;
    
    void clear_steps() { steps.clear(); }
  private:
    std::vector<Step> steps;
  };

} // namespace Sudoku

#endif // __PROCEEDING_HPP
