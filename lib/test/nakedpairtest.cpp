#include <cassert>

#include <sudoku/nakedpair.hpp>
#include <sudoku/step.hpp>
#include <sudoku/sudoku.hpp>

int main() {
  Sudoku::Sudoku s("000571068000000521510020070000090000060134257307000004480302705032050800005800002");

  assert(s.is_valid());
  assert(!s.is_finished());
  
  Sudoku::NakedPair naked_pair;

  Sudoku::Step step = naked_pair.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_pencilmark(27, 8));
  assert(s.get_pencilmark(29, 8));
  assert(s.get_pencilmark(46, 9));
  assert(step.apply(s));
  assert(!s.get_pencilmark(27, 8));
  assert(!s.get_pencilmark(29, 8));
  assert(!s.get_pencilmark(46, 9));

  assert(s.set_pencilmark(33, 1, false));
  assert(s.set_pencilmark(34, 1, false));
  
  step = naked_pair.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_pencilmark(30, 6));
  assert(s.get_pencilmark(32, 6));
  assert(s.get_pencilmark(34, 3));
  assert(s.get_pencilmark(51, 6));
  assert(step.apply(s));
  assert(!s.get_pencilmark(30, 6));
  assert(!s.get_pencilmark(32, 6));
  assert(!s.get_pencilmark(34, 3));
  assert(!s.get_pencilmark(51, 6));

  step = naked_pair.try_technique(s);
  assert(step.is_empty());

  return 0;
}
