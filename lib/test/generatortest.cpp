#include <iostream>
#include <cstdlib>
#include <ctime>

#include <sudoku/generator.hpp>
#include <sudoku/sudoku.hpp>

#include <sudoku/solver.hpp>
#include <sudoku/nakedsingle.hpp>
#include <sudoku/hiddensingle.hpp>
#include <sudoku/backtracking.hpp>

int main() {
  srand(time(NULL));
  
  Sudoku::NakedSingle naked;
  Sudoku::HiddenSingleRow hidden_row;
  Sudoku::HiddenSingleColumn hidden_column;
  Sudoku::HiddenSingleBox hidden_box;
  Sudoku::BackTracking back;
  
  Sudoku::Solver solver;
  solver.append_technique(naked);
  solver.append_technique(hidden_row);
  solver.append_technique(hidden_column);
  solver.append_technique(hidden_box);
  solver.append_technique(back);

  Sudoku::Sudoku sudoku;

  if (Sudoku::generate(Sudoku::Technique::EASY, 400, 600, 10, 
                       Sudoku::join(Sudoku::HORIZONTAL_REFLECTION, Sudoku::VERTICAL_REFLECTION),
                       solver, sudoku)) {
    sudoku.print(std::cout);
    std::cout << '\n';
    Sudoku::Proceeding p = solver.solve(sudoku, true);
    int score;
    Sudoku::Technique::Difficulty difficulty;
    p.evaluate(difficulty, score);
    std::cout << "Score: " << score << '\n' << "Difficulty: " << difficulty << '\n';
  } else {
    std::cout << "Fail!" << std::endl;
  }
  
  // Sudoku::Sudoku s = Sudoku::generate_full();
  // s.print(std::cout);
  // std::cout << '\n';
  
  return 0;
}
