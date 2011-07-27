#include <cassert>

#include <sudoku/fullhouse.hpp>
#include <sudoku/step.hpp>
#include <sudoku/sudoku.hpp>

int main() {
  Sudoku::Sudoku s("514697020279483516368251479806014732032068000001372600043025060107006000605100007");
  assert(s.is_valid());
  assert(!s.is_finished());
  
  Sudoku::FullHouse full_house;
  
  Sudoku::Step step = full_house.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_digit(77) == 0);
  assert(step.apply(s));
  assert(s.get_digit(77) == 9);

  step = full_house.try_technique(s);
  assert(step.is_empty());

  assert(s.set_digit(30, 9));
  step = full_house.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_digit(28) == 0);
  assert(step.apply(s));
  assert(s.get_digit(28) == 5);

  step = full_house.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_digit(39) == 0);
  assert(step.apply(s));
  assert(s.get_digit(39) == 5);
  
  step = full_house.try_technique(s);
  assert(step.is_empty());
  
  return 0;
}
