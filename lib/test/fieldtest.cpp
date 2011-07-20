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
    
    Positions p1;
    p1.assign(false);
    p1[4] = p1[7] = true;
    p1[10] = true;
    p1[21] = p1[22] = p1[23] = p1[25] = true;
    p1[29] = p1[30] = p1[31] = true;
    p1[36] = p1[38] = p1[39] = p1[40] = true;
    p1[53] = true;
    p1[60] = true;
    p1[63] = p1[65] = p1[67] = p1[68] = true;
    p1[72] = p1[74] = p1[75] = p1[76] = true;
    assert(p1 == f.get_digit_positions(1));
    
    Positions open;
    open.assign(true);
    open[2] = open[3] = open[5] = false;
    open[10] = open[11] = open[12] = open[15] = open[16] = false;
    open[18] = open[19] = open[24] = false;
    open[27] = open[28] = open[32] = open[34] = false;
    open[37] = open[41] = open[42] = false;
    open[45] = open[48] = open[49] = open[53] = false;
    open[55] = open[56] = open[58] = open[60] = false;
    open[64] = open[66] = false;
    open[77] = open[80] = false;
    assert(open == f.get_open_positions());
    
    Positions not_fixed = open;
    not_fixed[37] = true;
    assert(not_fixed == f.get_not_fixed_positions());

    Positions sole = not_op(open);
    assert(sole == f.get_sole_positions());
    
    Positions not_set_sole;
    not_set_sole.assign(false);
    not_set_sole[37] = true;
    assert(not_set_sole == f.get_not_set_sole_positions());
    
    Positions empty;
    empty.assign(false);
    assert(empty == f.get_empty_positions());
    
    Positions set1;
    set1.assign(false);
    set1[10] = set1[53] = set1[60] = true;
    assert(set1 == f.get_fixed_digit_positions(1));

    Positions p1_not_fixed = p1;
    p1_not_fixed[10] = p1_not_fixed[53] = p1_not_fixed[60] = false;
    assert(p1_not_fixed == f.get_not_fixed_digit_positions(1));

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
