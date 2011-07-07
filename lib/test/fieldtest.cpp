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

#include <cassert>
#include <iostream>
#include <sstream>

#include <sudoku/cell.hpp>
#include <sudoku/field.hpp>

using namespace Sudoku;

int main() {
  {
    Field f;
    for (int i = 0; i < 81; ++i) {
      assert(f[i].is_open());
      assert(f[i].get_digit() == 0);
      assert(!f[i].is_empty());
      assert(!f[i].is_sole());
      assert(!f[i].is_fixed());
      assert(f[i].get_count() == 9);
    }
  }
  
  {
    const std::string sudoku = "003902000012800390690000700430009050000005600200630001064090100070500000000004008";
    Field f(sudoku);
    std::stringstream s;
    s << f;
    assert(sudoku.compare(s.str()) == 0);
    Cell c0("578");
    assert(f[0] == c0);
    Cell c40("12478");
    assert(f[40] == c40);
  
    assert(!f.set_digit(40, 3));
    assert(f[40].get_digit() == 0);
    assert(f.set_digit(40, 1));
    
    Cell c22_new("45");
    assert(f[22] == c22_new);
    
    assert(f.set_digit(40, 0));
    Cell c22("145");
    assert(f[22] == c22);
    
    assert(!f.set_pencilmark(22, 2, true));
    assert(f.set_pencilmark(22, 4, false));
    Cell c22_new2("15");
    assert(f[22] == c22_new2);
    assert(f.set_pencilmark(22, 4, true));
    assert(f[22] == c22);
  }
  
  {
    Field f("003902000012800390690000700430009050000005600200630001064090100070500000000004008");
    std::list<Field> solutions;
    assert(f.solutions(2, solutions) == 1);
    assert(solutions.size() == 1);
    assert(solutions.front().is_finished());
  }
  
  {
    Field f("000902000012800390690000700430009050000005600200630001064090100070500000000004008");
    std::list<Field> solutions;
    assert(f.solutions(2, solutions) == 2);
    assert(solutions.size() == 2);
  }
  
  {
    Field f;
    std::list<Field> solutions;
    const int sols = f.solutions(10, solutions);
    assert(sols == 10);
    assert(solutions.size() == 10);
    // for (std::list<Field>::const_iterator i = solutions.begin(); i != solutions.end(); ++i) {
    //   std::cout << *i << std::endl;
    // }
  }
  
  return 0;
}
