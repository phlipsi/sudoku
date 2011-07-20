#include <sudoku/lastinstance.hpp>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <sudoku/action.hpp>
#include <sudoku/common_actions.hpp>
#include <sudoku/sudoku.hpp>

namespace Sudoku {

  Step LastInstance::do_try_technique(const Sudoku& sudoku) {
    for (int d = 1; d <= 9; ++d) {
      const Positions p = sudoku.get_fixed_digit_positions(d);
      if (count(p) == 8) {
        const Positions q = sudoku.get_not_fixed_digit_positions(d);
        const int pos = first(q);

        const std::string vague_hint = "Last Instance";
        const std::string hint = boost::str(boost::format("Last Instance for digit %1% in cell %2%:%3%") % d % (get_col(pos) + 1) % (get_row(pos) + 1));
        Actions proposed_actions;
        proposed_actions.push_back(boost::shared_ptr<Action>(new PlaceDigit(pos, d)));
        const int points = 6;
        return Step(*this, vague_hint, hint, Step::EASY, proposed_actions, points);
      }
    }
    return Step();
  }

} // namespace Sudoku
