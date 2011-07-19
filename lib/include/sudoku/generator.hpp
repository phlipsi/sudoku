#ifndef __GENERATOR_HPP
#define __GENERATOR_HPP

#include <sudoku/technique.hpp>

namespace Sudoku {

  class Solver;
  class Sudoku;
  class Symmetry;
  
  Sudoku generate_full();

  bool generate(Technique::Difficulty difficulty,
                int min_score, int max_score,
                int max_fails,
                const Symmetry& symmetry,
                Solver& solver,
                Sudoku& sudoku);

} // namespace Sudoku

#endif // __GENERATOR_HPP
