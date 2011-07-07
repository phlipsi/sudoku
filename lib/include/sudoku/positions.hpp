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

#ifndef __POSITIONS_HPP
#define __POSITIONS_HPP

#include <boost/array.hpp>

namespace Sudoku {

  typedef boost::array<bool, 81> Positions;

  extern const boost::array<Positions, 9> ROWS;
  extern const boost::array<Positions, 9> COLS;
  extern const boost::array<Positions, 9> BOXES;
  extern const boost::array<Positions, 81> PEERS;
  extern const boost::array<Positions, 81> PROPER_PEERS;
  extern const Positions ALL_CELLS;

  inline int get_row(int i) { return i / 9; }
  inline int get_col(int i) { return i % 9; }
  inline int get_box(int i) { return 3 * (get_row(i) / 3) + get_col(i) / 3; }

} // namespace Sudoku

#endif // __POSITIONS_HPP
