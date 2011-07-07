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

#ifndef __ACTION_HPP
#define __ACTION_HPP

#include <list>
#include <string>

#include <boost/shared_ptr.hpp>

#include <sudoku/sudoku.hpp>

namespace Sudoku {

  class Action {
  private:
    std::string name;
    std::string description;
  public:
    Action(const std::string& name, const std::string& description)
     : name(name), description(description) { }
    virtual ~Action() { }
    
    const std::string& get_name() const { return name; }
    const std::string& get_description() const { return description; }
    
    virtual bool do_action(Sudoku& sudoku) const = 0;
  };
  
  typedef std::list< boost::shared_ptr<Action> > Actions;

  bool execute_actions(Sudoku& sudoku, const Actions& actions);

} // namespace Sudoku

#endif // __ACTION_HPP
