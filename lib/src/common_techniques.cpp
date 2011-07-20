#include <sudoku/common_techniques.hpp>

#include <sudoku/solver.hpp>

namespace Sudoku {

  FullHouse full_house = FullHouse();
  LastInstance last_instance = LastInstance();
  HiddenSingleRow hidden_row = HiddenSingleRow();
  HiddenSingleColumn hidden_column = HiddenSingleColumn();
  HiddenSingleBox hidden_box = HiddenSingleBox();
  NakedSingle naked_single = NakedSingle();
  NakedPair naked_pair = NakedPair();
  BackTracking back_tracking = BackTracking();

  void register_common_techniques(Solver& solver) {
    solver.append_technique(full_house);
    solver.append_technique(last_instance);
    solver.append_technique(hidden_row);
    solver.append_technique(hidden_column);
    solver.append_technique(hidden_box);
    solver.append_technique(naked_single);
    solver.append_technique(naked_pair);
    solver.append_technique(back_tracking);
  }

}
