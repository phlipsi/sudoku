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
#include <cassert>
#include <string>

#include <sudoku/sudoku.hpp>
#include <sudoku/action.hpp>
#include <sudoku/nakedsingle.hpp>
#include <sudoku/hiddensingle.hpp>
#include <sudoku/backtracking.hpp>

// using namespace Sudoku;

int main() {
  Sudoku::Sudoku s("502009000000005000308020009000000084005002600910068700000076140000100200003500000");
  assert(s.unique());

  Sudoku::NakedSingle naked;
  Sudoku::Step step1 = naked.try_technique(s);
  assert(!step1.is_empty());
  // assert(proposed_actions.size() == 1);
  std::cout << step1.get_vague_hint() << std::endl;
  std::cout << step1.get_hint() << std::endl;
  
  assert(step1.apply(s));
  Sudoku::Sudoku s2("502009000000005000308020009000000084005002600910068700000076140000100200003500000");
  assert(s2.set_digit(47, 4));
  assert(s == s2);
  
  Sudoku::HiddenSingleBox hidden_box;
  Sudoku::Step step2 = hidden_box.try_technique(s);
  assert(!step2.is_empty());
  // assert(proposed_actions.size() == 1);
  std::cout << step2.get_vague_hint() << std::endl;
  std::cout << step2.get_hint() << std::endl;
  
  assert(step2.apply(s));
  assert(s2.set_digit(72, 1));
  assert(s == s2);

  Sudoku::HiddenSingleColumn hidden_column;
  Sudoku::Step step3 = hidden_column.try_technique(s);
  assert(!step3.is_empty());
  // assert(proposed_actions.size() == 1);
  std::cout << step3.get_vague_hint() << std::endl;
  std::cout << step3.get_hint() << std::endl;
  
  assert(step3.apply(s));
  assert(s2.set_digit(11, 1));
  assert(s == s2);

  Sudoku::HiddenSingleRow hidden_row;
  Sudoku::Step step4 = hidden_row.try_technique(s);
  assert(!step4.is_empty());
  // assert(proposed_actions.size() == 1);
  std::cout << step4.get_vague_hint() << std::endl;
  std::cout << step4.get_hint() << std::endl;
  
  assert(step4.apply(s));
  assert(s2.set_digit(73, 2));
  assert(s == s2);

  Sudoku::Step step5 = hidden_box.try_technique(s);
  assert(!step5.is_empty());
  // assert(proposed_actions.size() == 1);
  std::cout << step5.get_vague_hint() << std::endl;
  std::cout << step5.get_hint() << std::endl;
  
  assert(step5.apply(s));
  assert(s2.set_digit(27, 2));
  assert(s == s2);
  
  Sudoku::Step step6 = naked.try_technique(s);
  assert(!step6.is_empty());
  // assert(proposed_actions.size() == 1);
  std::cout << step6.get_vague_hint() << std::endl;
  std::cout << step6.get_hint() << std::endl;
  
  assert(step6.apply(s));
  assert(s2.set_digit(48, 3));
  assert(s == s2);

  Sudoku::BackTracking back;
  Sudoku::Step step7 = back.try_technique(s);
  assert(!step7.is_empty());
  // assert(proposed_actions.size() == 1);
  std::cout << step7.get_vague_hint() << std::endl;
  std::cout << step7.get_hint() << std::endl;

  assert(step7.apply(s));
  assert(s2.set_digit(1, 7));
  assert(s == s2);

  return 0;
}
