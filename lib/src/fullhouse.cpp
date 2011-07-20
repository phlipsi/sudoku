#include <sudoku/fullhouse.hpp>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <sudoku/action.hpp>
#include <sudoku/common_actions.hpp>
#include <sudoku/sudoku.hpp>

namespace Sudoku {

  Step FullHouse::do_try_technique(const Sudoku& sudoku) {
    const Positions p = sudoku.get_not_fixed_positions();
    for (int j = 0; j < 9; ++j) {
      if (is_sole(and_op(p, ROWS[j]))) {
        const std::string vague_hint = "Full House";
        const std::string hint = boost::str(boost::format("Full House in row %1%") % (j + 1));
        Actions proposed_actions;
        
        Pencilmarks already;
        already.assign(true);
        int where = -1;
        for (int i = 0; i < 9; ++i) {
          const int d = sudoku[9 * j + i].get_digit();
          if (d != 0) {
            already[d - 1] = false;
          } else {
            where = i;
          }
        }
        assert(where != -1);
        const int digit = first(already) + 1;
        proposed_actions.push_back(boost::shared_ptr<Action>(new PlaceDigit(9 * j + where, digit)));
        const int points = 4;
        return Step(*this, vague_hint, hint, Step::EASY, proposed_actions, points);
      }
      if (is_sole(and_op(p, COLS[j]))) {
        const std::string vague_hint = "Full House";
        const std::string hint = boost::str(boost::format("Full House in column %1%") % (j + 1));
        Actions proposed_actions;
        
        Pencilmarks already;
        already.assign(true);
        int where = -1;
        for (int i = 0; i < 9; ++i) {
          const int d = sudoku[9 * i + j].get_digit();
          if (d != 0) {
            already[d - 1] = false;
          } else {
            where = i;
          }
        }
        assert(where != -1);
        const int digit = first(already) + 1;
        proposed_actions.push_back(boost::shared_ptr<Action>(new PlaceDigit(9 * where + j, digit)));
        const int points = 4;
        return Step(*this, vague_hint, hint, Step::EASY, proposed_actions, points);
      }
      if (is_sole(and_op(p, BOXES[j]))) {
        const std::string vague_hint = "Full House";
        const std::string hint = boost::str(boost::format("Full House in box %1%") % (j + 1));
        Actions proposed_actions;
        
        Pencilmarks already;
        already.assign(true);
        int where = -1;
        for (int i = 0; i < 81; ++i) {
          if (BOXES[j][i]) {
            const int d = sudoku[i].get_digit();
            if (d != 0) {
              already[d - 1] = false;
            } else {
              where = i;
            }
          }
        }
        assert(where != -1);
        const int digit = first(already) + 1;
        proposed_actions.push_back(boost::shared_ptr<Action>(new PlaceDigit(where, digit)));
        const int points = 4;
        return Step(*this, vague_hint, hint, Step::EASY, proposed_actions, points);
      }
    }
    return Step();
  }

} // namespace Sudoku
