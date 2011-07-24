#ifndef __GENERATOR_HPP
#define __GENERATOR_HPP

#include <sudoku/step.hpp>

namespace Sudoku {

  class Solver;
  class Sudoku;
  class Symmetry;
  
  Sudoku generate_full();

  class Info {
  public:
    Info(bool success,
         int unique_fails,
         int unsolvable_fails,
         int too_difficult_fails)
    : success(success),
      unique_fails(unique_fails),
      unsolvable_fails(unsolvable_fails),
      too_difficult_fails(too_difficult_fails) { }
      
    operator bool() const { return success; }
    int get_unique_fails() const { return unique_fails; }
    int get_unsolvable_fails() const { return unsolvable_fails; }
    int get_too_difficult_fails() const { return too_difficult_fails; }
  private:
    bool success;
    int unique_fails;
    int unsolvable_fails;
    int too_difficult_fails;
  };

  Info generate(Step::Difficulty difficulty,
                int min_score, int max_score,
                int max_fails,
                const Symmetry& symmetry,
                Solver& solver,
                Sudoku& sudoku);

} // namespace Sudoku

#endif // __GENERATOR_HPP
