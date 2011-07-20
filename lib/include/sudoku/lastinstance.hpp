#ifndef __LASTINSTANCE_HPP
#define __LASTINSTANCE_HPP

#include <sudoku/technique.hpp>

namespace Sudoku {

  class LastInstance : public Technique {
  public:
    LastInstance() : Technique("Last Instance", "Eight instances of a digit are already set", "Philipp Wähnert", 0, false) { }
  protected:
    virtual Step do_try_technique(const Sudoku& sudoku);
  };

} // namespace Sudoku

#endif // __LASTINSTANCE_HPP
