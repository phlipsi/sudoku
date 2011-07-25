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

#include <iostream>

#include <sudoku/solver.hpp>
#include <sudoku/step.hpp>

#include <sudoku/common_techniques.hpp>
// #include <sudoku/technique.hpp>

int main() {
  // Sudoku::Sudoku sudoku("502009000000005000308020009000000084005002600910068700000076140000100200003500000");
  // Sudoku::Sudoku sudoku("080000200203090807065018000000000070059000100006000508490025000000800010030006009");
  // Sudoku::Sudoku sudoku("005160000600073000300005706000030691139756482862491007401000005000500008000007200");
  Sudoku::Sudoku sudoku("010000060003106700760204051006509200000000000005801400250608094009405100040000080");
  
  Sudoku::Solver solver;
  register_common_techniques(solver);

  Sudoku::Proceeding p = solver.solve(sudoku, Sudoku::Step::TOUGH, 2000, true);
  if (p.is_solved()) {
    Sudoku::Step::Difficulty max_diff = Sudoku::Step::EASY;
    int score = 0;
    p.evaluate(max_diff, score);
    std::cout << "Difficulty: " << max_diff << '\n' << "Score: " << score << std::endl;
    for (int i = 0; i < p.count_steps(); ++i) {
      std::cout << i << '\t' << p.get_step(i).get_hint() << '\t' << p.get_step(i).get_points() << std::endl;
    }
  } else {
    std::cout << "Can't solve sudoku" << std::endl;
  }
  
  return 0;
}
