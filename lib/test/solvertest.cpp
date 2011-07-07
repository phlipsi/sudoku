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
#include <sudoku/nakedsingle.hpp>
#include <sudoku/hiddensingle.hpp>
#include <sudoku/backtracking.hpp>
#include <sudoku/technique.hpp>

int main() {
  // Sudoku::Sudoku sudoku("502009000000005000308020009000000084005002600910068700000076140000100200003500000");
  Sudoku::Sudoku sudoku("080000200203090807065018000000000070059000100006000508490025000000800010030006009");


  Sudoku::NakedSingle naked;
  Sudoku::HiddenSingleRow hidden_row;
  Sudoku::HiddenSingleColumn hidden_column;
  Sudoku::HiddenSingleBox hidden_box;
  Sudoku::BackTracking back;
  
  Sudoku::Solver solver;
  solver.append_technique(naked);
  solver.append_technique(hidden_row);
  solver.append_technique(hidden_column);
  solver.append_technique(hidden_box);
  solver.append_technique(back);

  Sudoku::Proceeding p;
  if (solver.solve(sudoku, p)) {
    Sudoku::Technique::Difficulty max_diff = Sudoku::Technique::EASY;
    int score = 0;
    p.evaluate(max_diff, score);
    std::cout << "Difficulty: " << max_diff << '\n' << "Score: " << score << std::endl;
    for (int i = 0; i < p.count_steps(); ++i) {
      std::cout << i << '\t' << p.get_step(i).get_hint() << std::endl;
    }
  } else {
    std::cout << "Can't solve sudoku" << std::endl;
  }
  
  return 0;
}
