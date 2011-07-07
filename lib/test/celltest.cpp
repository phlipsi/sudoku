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

#include <sudoku/cell.hpp>

using namespace Sudoku;

int main() {
  Cell c;
  assert(c.get_count() == 9);
  assert(c.is_sole() == false);
  assert(c.is_empty() == false);
  assert(c.is_open() == true);
  assert(c.get_digit() == 0);
  
  c.set(1, false);
  assert(c.get_count() == 8);
  assert(c.is_sole() == false);
  assert(c.is_empty() == false);
  assert(c.is_open() == true);
  assert(c.get_digit() == 0);

  c.set(2, false);
  c.set(3, false);
  c.set(4, false);
  c.set(5, false);
  c.set(6, false);
  c.set(7, false);
  c.set(8, false);
  assert(c.get_count() == 1);
  assert(c.is_sole() == true);
  assert(c.is_empty() == false);
  assert(c.is_open() == false);
  assert(c.get_digit() == 0);
  
  c.set(8, false);
  assert(c.get_count() == 1);

  c.set_to_digit(9);
  assert(c.get_count() == 1);
  assert(c.is_sole() == true);
  assert(c.is_empty() == false);
  assert(c.is_open() == false);
  assert(c.get_digit() == 9);
  
  Cell c2(9);
  assert(c == c2);

  return 0;
}
