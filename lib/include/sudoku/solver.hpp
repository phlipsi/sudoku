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

#ifndef __SOLVER_HPP
#define __SOLVER_HPP

#include <list>
#include <utility>

#include <sudoku/proceeding.hpp>
#include <sudoku/step.hpp>
#include <sudoku/technique.hpp>
#include <sudoku/techniquelist.hpp>

namespace Sudoku {

  class Sudoku;
  class Proceeding;

  class Solver {
  public:
    typedef TechniqueList::iterator iterator;
    typedef TechniqueList::const_iterator const_iterator;
    
    void append_technique(Technique& t) { list.append_technique(t); }

    iterator insert_technique(iterator position, Technique& t) {
      return list.insert_technique(position, t);
    }    

    iterator delete_technique(iterator position) {
      return list.delete_technique(position);
    }

    void clear_techniques() {
      list.clear_techniques();
    }
    
    void activate(iterator position, bool active = true) {
      list.activate(position, active);
    }

    const_iterator find_technique(const Technique::HashType& hash) const {
      return list.find_technique(hash);
    }
    
    iterator find_technique(const Technique::HashType& hash) {
      return list.find_technique(hash);
    }

    iterator begin() { return list.begin(); }
    iterator end() { return list.end(); }
    
    const_iterator begin() const { return list.begin(); }
    const_iterator end() const { return list.end(); }
    
    Proceeding solve(const Sudoku& sudoku,
                     Step::Difficulty max_difficulty,
                     int max_score,
                     bool assume_uniqueness);
  private:
    TechniqueList list;
  };

} // namespace Sudoku

#endif // __SOLVER_HPP
