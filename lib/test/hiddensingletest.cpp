#include <cassert>

#include <sudoku/hiddensingle.hpp>
#include <sudoku/step.hpp>
#include <sudoku/sudoku.hpp>

int main() {
  Sudoku::Sudoku s("000000401180000920700600080003027100000000003005043800900500070860000510000000208");
  assert(s.is_valid());
  assert(!s.is_finished());
  
  Sudoku::HiddenSingleRow hidden_row;
  
  Sudoku::Step step = hidden_row.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_digit(30) == 0);
  assert(step.apply(s));
  assert(s.get_digit(30) == 8);
  
  Sudoku::HiddenSingleColumn hidden_column;
  
  step = hidden_column.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_digit(53) == 0);
  assert(step.apply(s));
  assert(s.get_digit(53) == 2);

  Sudoku::HiddenSingleBox hidden_box;
  
  step = hidden_box.try_technique(s);
  assert(!step.is_empty());
  assert(s.get_digit(17) == 0);
  assert(step.apply(s));
  assert(s.get_digit(17) == 7);

  s.assign("359000461186000927724600385493827156218000743675143892930500674860000519540000238");
  step = hidden_box.try_technique(s);
  assert(step.is_empty());
  step = hidden_column.try_technique(s);
  assert(step.is_empty());
  step = hidden_row.try_technique(s);
  assert(step.is_empty());
  
  return 0;
}
