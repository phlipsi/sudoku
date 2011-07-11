#include <iostream>

#include <sudoku/boolarray.hpp>
#include <sudoku/symmetry.hpp>

int main() {
  // Sudoku::HORIZONTAL_REFLECTION.print(std::cout);
  // std::cout << '\n';
  // Sudoku::VERTICAL_REFLECTION.print(std::cout);
  Sudoku::Symmetry s = join(Sudoku::HORIZONTAL_REFLECTION, Sudoku::VERTICAL_REFLECTION);
  // std::cout << '\n';
  // s.print(std::cout);

  for (Sudoku::Symmetry::const_iterator i = s.begin(); i != s.end(); ++i) {
    Sudoku::Positions p = *i;
    using namespace Sudoku;
    std::cout << p << std::endl;
  }
  return 0;
}
