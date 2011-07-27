#include <cassert>

#include <sudoku/lastinstance.hpp>
#include <sudoku/step.hpp>
#include <sudoku/sudoku.hpp>

int main() {
  Sudoku::Sudoku s("594671382028439156136852479247918635853267941961345728382796514605124893419583267");
  assert(s.is_valid());
  assert(!s.is_finished());
  
  Sudoku::LastInstance last_instance;
  
  Sudoku::Step step = last_instance.try_technique(s);
  assert(step.is_empty());

  assert(s.set_digit(9, 7));
  step = last_instance.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_digit(64) == 0);
  assert(step.apply(s));
  assert(s.get_digit(64) == 7);
  
  return 0;
}
