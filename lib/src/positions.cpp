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

#include <sudoku/positions.hpp>

#include <sudoku/boolarray.hpp>

namespace Sudoku {

  // Warning: These routines aren't optimised to be executed very
  // efficiently. I've choosen a clear implementation because
  // they only run once.
  boost::array<Positions, 9> init_rows() {
    boost::array<Positions, 9> result;
    for (int row = 0; row < 9; ++row) {
      Positions& p = result[row];
      p.assign(false);
      for (int column = 0; column < 9; ++column)
        p[column+9*row] = true;
    }
    return result;
  }

  boost::array<Positions, 9> init_columns() {
    boost::array<Positions, 9> result;
    for (int column = 0; column < 9; ++column) {
      Positions& p = result[column];
      p.assign(false);
      for (int row = 0; row < 9; ++row)
        p[column+9*row] = true;
    }
    return result;
  }

  boost::array<Positions, 9> init_boxes() {
    boost::array<Positions, 9> result;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) {
        Positions& p = result[3*j+i];
        p.assign(false);
        for (int y = 0; y < 3; ++y)
          for (int x = 0; x < 3; ++x)
            p[9*(y+3*j) + (x+3*i)] = true;
      }
    return result;
  }

  // boost::array<boost::array<Positions, 3>, 3> init_boxes() {
  //   boost::array<boost::array<Positions, 3>, 3> result = { false };
  //   for (int i = 0; i < 3; ++i)
  //     for (int j = 0; j < 3; ++j) {
  //       Positions& p = result[i][j];
  //       for (int x = 0; x < 3; ++x)
  //         for (int y = 0; y < 3; ++y)
  //           p[9*(y+3*j) + (x+3*i)] = true;
  //     }
  //   return result;
  // }

  boost::array<Positions, 81> init_peers() {
    boost::array<Positions, 81> result;
    for (int x = 0; x < 9; ++x)
      for (int y = 0; y < 9; ++y) {
        Positions& peers = result[9*y + x];
        peers = ROWS[y];
        or_assign(peers, COLS[x]);
        or_assign(peers, BOXES[x/3 + 3*(y/3)]);
      }
    return result;
  }

  // boost::array<boost::array<Positions, 9>, 9> init_peers() {
  //   boost::array<boost::array<Positions, 9>, 9> result;
  //   for (int x = 0; x < 9; ++x)
  //     for (int y = 0; y < 9; ++y)
  //       result[x][y] = rows[y] | columns[x] | boxes[x/3][y/3];
  //   return result;
  // }

  boost::array<Positions, 81> init_proper_peers() {
    boost::array<Positions, 81> result = PEERS;
    for (int pos = 0; pos < 81; ++pos) {
      result[pos][pos] = false;
    }
    return result;
  }
  
  Positions init_all_cells() {
    Positions result;
    for (int pos = 0; pos < 81; ++pos)
      result[pos] = true;
    return result;
  }

  // boost::array<boost::array<Positions, 9>, 9> init_proper_peers() {
  //   boost::array<boost::array<Positions, 9>, 9> result = peers;
  //   for (int x = 0; x < 9; ++x)
  //     for (int y = 0; y < 9; ++y)
  //       result[x][y][x+9*y] = false;
  //   return result;
  // }
  
  const boost::array<Positions, 9> ROWS = init_rows();
  const boost::array<Positions, 9> COLS = init_columns();
  const boost::array<Positions, 9> BOXES = init_boxes();

  const boost::array<Positions, 81> PEERS = init_peers();
  const boost::array<Positions, 81> PROPER_PEERS = init_proper_peers();

  const Positions ALL_CELLS = init_all_cells();

  // const boost::array<boost::array<Field::Positions, 3>, 3> boxes = init_boxes();
  // const boost::array<boost::array<Field::Positions, 9>, 9> peers = init_peers();
  // const boost::array<boost::array<Field::Positions, 9>, 9> proper_peers = init_proper_peers();

} // namespace Sudoku
