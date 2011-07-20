#include <iostream>
#include <cstdlib>
#include <ctime>

#include <sudoku/generator.hpp>
#include <sudoku/sudoku.hpp>
#include <sudoku/step.hpp>

#include <sudoku/solver.hpp>
#include <sudoku/nakedsingle.hpp>
#include <sudoku/hiddensingle.hpp>
#include <sudoku/backtracking.hpp>
#include <sudoku/fullhouse.hpp>
#include <sudoku/lastinstance.hpp>

int main() {
  srand(time(NULL));
  
  Sudoku::FullHouse full_house;
  Sudoku::LastInstance last_instance;
  Sudoku::HiddenSingleRow hidden_row;
  Sudoku::HiddenSingleColumn hidden_column;
  Sudoku::HiddenSingleBox hidden_box;
  Sudoku::NakedSingle naked;
  Sudoku::BackTracking back;
  
  Sudoku::Solver solver;
  solver.append_technique(full_house);
  solver.append_technique(last_instance);
  solver.append_technique(hidden_row);
  solver.append_technique(hidden_column);
  solver.append_technique(hidden_box);
  solver.append_technique(naked);
  solver.append_technique(back);

  Sudoku::Sudoku sudoku;

  if (Sudoku::generate(Sudoku::Step::EASY, 350, 600, 20,
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
