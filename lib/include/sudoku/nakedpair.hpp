#ifndef __NAKEDPAIR_HPP
#define __NAKEDPAIR_HPP

#include <sudoku/technique.hpp>

namespace Sudoku {

  class NakedPair : public Technique {
  public:
    NakedPair() : Technique("Naked Pair", "Two cells containing two candidates together", "Philipp Wähnert", 0, false) { }
  protected:
    virtual Step do_try_technique(const Sudoku& sudoku);
  };

} // namespace Sudoku

#endif // __NAKEDPAIR_HPP
