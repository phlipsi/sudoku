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

#ifndef __TECHNIQUE_HPP
#define __TECHNIQUE_HPP

#include <list>
#include <string>

#include <boost/shared_ptr.hpp>

#include <sudoku/action.hpp>
#include <sudoku/labeled.hpp>
#include <sudoku/sudoku.hpp>
#include <sudoku/step.hpp>

namespace Sudoku {

  class Technique : public Labeled {
  public:
    Technique(const std::string& name,
              const std::string& description,
              const std::string& author,
              int admin_score,
              bool requires_uniqueness,
              const HashType& module)
      : Labeled(name, description, author, module),
        admin_score(admin_score),
        requires_uniqueness(requires_uniqueness),
        usages(0), tries(0)
    { }
    
    Technique(const std::string& name,
              const std::string& description,
              const std::string& author,
              int admin_score,
              bool requires_uniqueness)
      : Labeled(name, description, author, nil_hash()),
        admin_score(admin_score),
        requires_uniqueness(requires_uniqueness),
        usages(0), tries(0)
    { }

    virtual ~Technique() { }
    
    int get_admin_score() const { return admin_score; }
    int get_usages() const { return usages; }
    int get_tries() const { return tries; }
    bool does_require_uniqueness() const { return requires_uniqueness; }
    
    void reset_counter() {
      tries = 0;
      usages = 0;
    }
    
    Step try_technique(const Sudoku& sudoku) {
      ++tries;
      Step step = do_try_technique(sudoku);
      if (!step.is_empty()) {
        if (usages == 0) {
          step.inc_points(admin_score);
        }
        ++usages;
      }
      return step;
    }
  
  protected:
    virtual Step do_try_technique(const Sudoku& sudoku) = 0;
  
  private:
    int admin_score;
    bool requires_uniqueness;
    int usages;
    int tries;
  };

  // typedef std::list< boost::shared_ptr<Technique> > Techniques;

} // namespace Sudoku

#endif // __TECHNIQUE_HPP
