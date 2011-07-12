#include <iostream>
#include <map>

// #include <sudoku/boolarray.hpp>
#include <sudoku/symmetry.hpp>
#include <sudoku/positions.hpp>

using namespace Sudoku;

void test_symmetry(const Symmetry& s) {
  std::map<int, Symmetry::const_iterator> m;
  for (Symmetry::const_iterator i = s.begin(); i != s.end(); ++i) {
    for (unsigned int j = 0; j < 81; ++j) {
      if ((*i)[j]) {
        std::pair<std::map<int, Symmetry::const_iterator>::iterator, bool> result
          = m.insert(std::make_pair(j, i));
        assert(result.second);
      }
    }
  }
  for (unsigned int j = 0; j < 81; ++j) {
    std::map<int, Symmetry::const_iterator>::iterator it = m.find(j);
    assert(it != m.end());
  }
}


int main() {
  test_symmetry(Symmetry());
  test_symmetry(HORIZONTAL_REFLECTION);
  test_symmetry(VERTICAL_REFLECTION);
  test_symmetry(ROTATION_180);
  test_symmetry(DIAGONAL_REFLECTION);
  test_symmetry(ANTIDIAGONAL_REFLECTION);
  test_symmetry(join(HORIZONTAL_REFLECTION, HORIZONTAL_REFLECTION));
  test_symmetry(join(HORIZONTAL_REFLECTION, VERTICAL_REFLECTION));
  test_symmetry(join(HORIZONTAL_REFLECTION, ROTATION_180));
  test_symmetry(join(HORIZONTAL_REFLECTION, DIAGONAL_REFLECTION));
  test_symmetry(join(HORIZONTAL_REFLECTION, ANTIDIAGONAL_REFLECTION));

  Positions p;
  p.assign(false);
  for (unsigned int i = 0; i < 9; ++i) {
    p[i] = true;
    p[i + 72] = true;
    p[9 * i] = true;
    p[9 * i + 8] = true;
  }
  assert(HORIZONTAL_REFLECTION.satisfies(p));
  assert(VERTICAL_REFLECTION.satisfies(p));
  assert(ROTATION_180.satisfies(p));
  assert(DIAGONAL_REFLECTION.satisfies(p));
  assert(ANTIDIAGONAL_REFLECTION.satisfies(p));

  return 0;
}
