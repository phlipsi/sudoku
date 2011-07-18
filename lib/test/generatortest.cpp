#include <iostream>
#include <cstdlib>
#include <ctime>

#include <sudoku/generator.hpp>
#include <sudoku/sudoku.hpp>

// #include <sudoku/solver.hpp>
// #include <sudoku/nakedsingle.hpp>
// #include <sudoku/hiddensingle.hpp>
// #include <sudoku/backtracking.hpp>

int main() {
  srand(time(NULL));
  
  // Sudoku::NakedSingle naked;
  // Sudoku::HiddenSingleRow hidden_row;
  // Sudoku::HiddenSingleColumn hidden_column;
  // Sudoku::HiddenSingleBox hidden_box;
  // Sudoku::BackTracking back;
  
  // Sudoku::Solver solver;
  // solver.append_technique(naked);
  // solver.append_technique(hidden_row);
  // solver.append_technique(hidden_column);
  // solver.append_technique(hidden_box);
  // solver.append_technique(back);
  
  int misses = 0;
  Sudoku::Sudoku s = Sudoku::generate_full(misses);
  s.print(std::cout);
  std::cout << ": " << misses << '\n';
  return 0;
}
