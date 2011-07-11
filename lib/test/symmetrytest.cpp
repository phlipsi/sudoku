#include <iostream>

#include <sudoku/boolarray.hpp>
#include <sudoku/symmetry.hpp>

int main() {
  Sudoku::Symmetry s = join(Sudoku::HORIZONTAL_REFLECTION, Sudoku::VERTICAL_REFLECTION);
  s.print(std::cout);
  assert(s.count_classes() == 25);

  std::cout << '\n';
  Sudoku::Symmetry t = join(Sudoku::DIAGONAL_REFLECTION, Sudoku::ANTIDIAGONAL_REFLECTION);
  t.print(std::cout);
  
  std::cout << '\n';
  Sudoku::Symmetry u = join(s, t);
  u = join(u, Sudoku::ROTATION_180);
  u.print(std::cout);

  return 0;
}
