#include <iostream>
#include <cstdlib>
#include <ctime>

#include <sudoku/generator.hpp>
#include <sudoku/technique.hpp>
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

  Sudoku::Sudoku s;
  if (Sudoku::generate(Sudoku::Technique::EASY,
                       100,
                       500,
                       500,
                       // join(join(Sudoku::HORIZONTAL_REFLECTION, Sudoku::VERTICAL_REFLECTION), Sudoku::DIAGONAL_REFLECTION),
                       // Sudoku::HORIZONTAL_REFLECTION,
                       join(Sudoku::HORIZONTAL_REFLECTION, Sudoku::VERTICAL_REFLECTION),
                       solver,
                       s)) {
    std::cout << "Juhu!" << std::endl;
    s.print(std::cout);
    std::cout << '\n';
  } else {
    std::cout << "Fail!" << std::endl;
  }
  return 0;
}
