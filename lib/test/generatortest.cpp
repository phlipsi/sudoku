#include <iostream>
#include <cstdlib>
#include <ctime>

#include <sudoku/generator.hpp>
#include <sudoku/sudoku.hpp>
#include <sudoku/step.hpp>

#include <sudoku/solver.hpp>
#include <sudoku/common_techniques.hpp>

int main() {
  srand(time(NULL));
    
  Sudoku::Solver solver;
  solver.append_technique(Sudoku::full_house);
  solver.append_technique(Sudoku::last_instance);
  solver.append_technique(Sudoku::hidden_row);
  solver.append_technique(Sudoku::hidden_column);
  solver.append_technique(Sudoku::hidden_box);
  solver.append_technique(Sudoku::naked_single);
  solver.append_technique(Sudoku::naked_pair);
  // solver.append_technique(Sudoku::back_tracking);

  Sudoku::Sudoku sudoku;

  if (Sudoku::generate(Sudoku::Step::MODERATE, 1, 1000, 500,
                       // Sudoku::join(Sudoku::HORIZONTAL_REFLECTION, Sudoku::VERTICAL_REFLECTION),
                       Sudoku::join(Sudoku::join(Sudoku::HORIZONTAL_REFLECTION, Sudoku::VERTICAL_REFLECTION), Sudoku::ROTATION_180),
                       // Sudoku::Symmetry(),
                       solver, sudoku)) {
    sudoku.print(std::cout);
    std::cout << '\n';
    Sudoku::Proceeding p = solver.solve(sudoku, true);
    int score;
    Sudoku::Step::Difficulty difficulty;
    p.evaluate(difficulty, score);
    std::cout << "Score: " << score << '\n'
              << "Difficulty: " << difficulty << '\n'
              << "Steps: " << p.count_steps() << '\n';
    // p.print(std::cout);
    std::cout << '\n';
  } else {
    std::cout << "Fail!" << std::endl;
  }
  
  // Sudoku::Sudoku s = Sudoku::generate_full();
  // s.print(std::cout);
  // std::cout << '\n';
  
  return 0;
}
