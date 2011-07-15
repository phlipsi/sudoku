#ifndef __GENERATOR_HPP
#define __GENERATOR_HPP

#include <sudoku/technique.hpp>

namespace Sudoku {

  class Symmetry;
  class Solver;

  bool generate(Technique::Difficulty max_difficulty,
                int min_score, int max_score, int max_attempts,
                const Symmetry& symmetry,
                Solver& solver,
                Sudoku& sudoku);

  /*class Generator {
  public:
    Generator(Technique::Difficulty difficulty,
              int min_score, int max_score, int max_attempts,
              Symmetry symmetry,
              Solver& solver)
      : difficulty(difficulty),
        min_score(min_score), max_score(max_score), max_attempts(max_attempts)
        symmetry(symmetry) { }
    
    void 
  private:
    Technique::Difficulty difficulty;
    int min_score, max_score, max_attempts;
    Symmetry symmetry;
  };*/

} // namespace Sudoku

#endif // __GENERATOR_HPP
