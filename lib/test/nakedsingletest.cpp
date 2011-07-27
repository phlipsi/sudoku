#include <cassert>

#include <sudoku/nakedsingle.hpp>
#include <sudoku/step.hpp>
#include <sudoku/sudoku.hpp>

int main() {
  Sudoku::Sudoku s("359000461186000927724600385493827156218000743675143892930500674860000519540000238");
  assert(s.is_valid());
  assert(!s.is_finished());
  
  Sudoku::NakedSingle naked_single;

  Sudoku::Step step = naked_single.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_digit(39) == 0);
  assert(step.apply(s));
  assert(s.get_digit(39) == 9);

  s.assign("002008600080024030600501004008246500040853020005917800100409008090060010004000700");
  step = naked_single.try_technique(s);
  assert(step.is_empty());

  return 0;
}
