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

#ifndef __FIELD_HPP
#define __FIELD_HPP

#include <ostream>                // std::ostream in operator <<
#include <list>                   // std::list in solutions

#include <boost/array.hpp>        // boost::array in Field

#include <sudoku/cell.hpp>        // Cell in Field
#include <sudoku/pencilmarks.hpp> // Pencilmarks in get_pencilmarks
#include <sudoku/positions.hpp>   // Positions in get_..._positions
#include <sudoku/symmetry.hpp>

namespace Sudoku {

  class Field {
  public:
    Field() {
      clear();
    }
    
    Field(const std::string& sudoku) {
      assign(sudoku);
    }
    
    Field(const boost::array<int, 81>& f) {
      assign(f);
    }

    boost::array<int, 81> extract_digits() const {
      boost::array<int, 81> result;
      result.assign(0);
      for (int i = 0; i < 81; ++i) {
        result[i] = cells[i].get_digit();
      }
      return result;
    }

    const Cell& operator [] (int i) const { return cells[i]; }

    void assign(const std::string& sudoku);
    void assign(const boost::array<int, 81>& f);
    
    void restart_pencilmarks();
    bool set_pencilmark(int pos, int digit, bool state);
    bool get_pencilmark(int pos, int digit) const { return cells[pos].get(digit); }
    const Pencilmarks& get_pencilmarks(int pos) const { return cells[pos].get(); }

    void clear() {
      for (int i = 0; i < 81; ++i) {
        cells[i].clear();
      }
    }
    
    // Simple validity check, i.e. does every digit occure at most
    // once in every row, column and box and there aren't any empty cells
    bool is_valid() const;
    
    // Valid field with no unset cells
    bool is_finished() const;

    // Pleasy use this method instead of the plethora of methods like
    // get_***_positions() and so on
    template<typename Property>
    Positions get_positions(Property property) const {
      Positions result;
      Properties::select(cells.begin(), cells.end(), result.begin(), property);
      return result;
    }

    // Where're not yet set cells
    Positions get_open_positions() const {
      return get_positions(Cell::count() > 1);
    }
    
    Positions get_not_fixed_positions() const {
      return get_positions(Cell::digit() == 0);
    }
    
    // Where're already set cells or cells allowing only one digit
    Positions get_sole_positions() const {
      return get_positions(Cell::digit() != 0 || Cell::count() == 1);
    }
    
    Positions get_not_set_sole_positions() const {
      return get_positions(Cell::digit() == 0 && Cell::count() == 1);
    }
    
    // Where're completly empty cells (illegal sudoku state!)
    Positions get_empty_positions() const {
      return get_positions(Cell::count() == 0);
    }
    
    // Where's the given digit allowed
    Positions get_digit_positions(int digit) const {
      return get_positions(Cell::pencilmark(digit));
    }

    // Where's the given digit set
    Positions get_fixed_digit_positions(int digit) const {
      return get_positions(Cell::digit() == digit);
    }
    

    // Where's the given digit allowed but not set
    Positions get_not_fixed_digit_positions(int digit) const {
      return get_positions(Cell::pencilmark(digit) && Cell::digit() == 0);
    }

    // according to the cell's peers
    bool is_allowed(int pos, int digit) const;
    bool set_digit(int pos, int digit);
    int get_digit(int pos) { return cells[pos].get_digit(); }
    
    bool unique(int max_fails = -1) const {
      std::list<Field> sols;
      return solutions(2, sols, max_fails) == 1;
    }

    int count_solutions(int max, int max_fails = -1) const {
      std::list<Field> sols;
      return solutions(max, sols, max_fails);
    }

    int solutions(int max, std::list<Field>& sols, int max_fails = -1) const;

    int count_not_fixed() const {
      int result = 0;
      for (int i = 0; i < 81; ++i) {
        if (!cells[i].is_fixed()) ++result;
      }
      return result;
    }

    bool operator == (const Field& f) const {
      return cells == f.cells;
    }

    bool check_symmetry(const Symmetry& symmetry) const {
      const Positions p = get_open_positions();
      return symmetry.satisfies(p);
    }

  private:
    boost::array<Cell, 81> cells;
    
    void solutions_impl(boost::array<int, 81>& f, int next, int max, int& count, int max_fails, int& fails, std::list<Field>& sols) const;
  };
  
  inline std::ostream& operator << (std::ostream& stream, const Field& f) {
    for (int i = 0; i < 81; ++i) {
      stream << f[i].get_digit();
    }
    return stream;
  }

} // namespace Sudoku

#endif // __FIELD_HPP
