#ifndef __FULLHOUSE_HPP
#define __FULLHOUSE_HPP

#include <sudoku/technique.hpp>

namespace Sudoku {

  class FullHouse : public Technique {
  public:
    FullHouse() : Technique("Full House", "A row, column or box has only one free cell left", "Philipp Wähnert", 0, false) { }
  protected:
    virtual Step do_try_technique(const Sudoku& sudoku);
  };

} // namespace Sudoku

#endif // __FULLHOUSE_HPP
