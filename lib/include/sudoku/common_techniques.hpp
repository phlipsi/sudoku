#ifndef __COMMON_TECHNIQUES_HPP
#define __COMMON_TECHNIQUES_HPP

#include <sudoku/backtracking.hpp>
#include <sudoku/fullhouse.hpp>
#include <sudoku/hiddensingle.hpp>
#include <sudoku/lastinstance.hpp>
#include <sudoku/nakedpair.hpp>
#include <sudoku/nakedsingle.hpp>

namespace Sudoku {

  extern FullHouse full_house;
  extern LastInstance last_instance;
  extern HiddenSingleRow hidden_row;
  extern HiddenSingleColumn hidden_column;
  extern HiddenSingleBox hidden_box;
  extern NakedSingle naked_single;
  extern NakedPair naked_pair;
  extern BackTracking back_tracking;

  class Solver;
  
  void register_common_techniques(Solver& solver);

} // namespace

#endif // __COMMON_TECHNIQUES_HPP
