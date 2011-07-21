#include <sudoku/nakedpair.hpp>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <sudoku/action.hpp>
#include <sudoku/common_actions.hpp>
#include <sudoku/sudoku.hpp>

namespace Sudoku {

  Step NakedPair::do_try_technique(const Sudoku& sudoku) {
    const Positions pairs = sudoku.get_positions(Cell::count() == 2);
    for (int pos1 = first(pairs); pos1 != -1; pos1 = next(pairs, pos1)) {
      for (int pos2 = next(pairs, pos1); pos2 != -1; pos2 = next(pairs, pos2)) {
        if (PROPER_PEERS[pos1][pos2]) {
          const Positions common_peers = and_op(PROPER_PEERS[pos1], PROPER_PEERS[pos2]);
          const Pencilmarks& p = sudoku.get_pencilmarks(pos1);
          if (p == sudoku.get_pencilmarks(pos2)) {
            int digit1 = first(p) + 1;
            int digit2 = next(p, digit1 - 1) + 1;
            const Positions del_digit1 = and_op(common_peers, sudoku.get_positions(Cell::pencilmark(digit1)));
            const Positions del_digit2 = and_op(common_peers, sudoku.get_positions(Cell::pencilmark(digit2)));
            if (count(del_digit1) > 0 || count(del_digit2) > 0) {
              int common_row = get_row(pos1);
              if (common_row != get_row(pos2)) {
                common_row = -1;
              }
              int common_col = get_col(pos1);
              if (common_col != get_col(pos2)) {
                common_col = -1;
              }
              int common_box = get_box(pos1);
              if (common_box != get_box(pos2)) {
                common_box = -1;
              }
              std::string vague_hint;
              std::string hint;
              int points = 0;
              Step::Difficulty difficulty = Step::EASY;
              if (common_box != -1) {
                if (common_row != -1) {
                  vague_hint = "Locked Pair";
                  hint = boost::str(boost::format("Locked pair %1%,%2% in box %3% and row %4%") % digit1 % digit2 % (common_box + 1) % (common_row + 1));
                  difficulty = Step::MODERATE;
                  points = 40;
                } else if (common_col != -1) {
                  vague_hint = "Locked Pair";
                  hint = boost::str(boost::format("Locked pair %1%,%2% in box %3% and column %4%") % digit1 % digit2 % (common_box + 1) % (common_col + 1));
                  difficulty = Step::MODERATE;
                  points = 40;
                } else {
                  vague_hint = "Naked Pair";
                  hint = boost::str(boost::format("Naked pair %1%,%2% in box %3%") % digit1 % digit2 % (common_box + 1));
                  difficulty = Step::TOUGH;
                  points = 60;
                }
              } else if (common_col != -1) {
                vague_hint = "Naked Pair";
                hint = boost::str(boost::format("Naked pair %1%,%2% in column %3%") % digit1 % digit2 % (common_col + 1));
                difficulty = Step::TOUGH;
                points = 60;
              } else if (common_row != -1) {
                vague_hint = "Naked Pair";
                hint = boost::str(boost::format("Naked pair %1%,%2% in row %3%") % digit1 % digit2 % (common_row + 1));
                difficulty = Step::TOUGH;
                points = 60;
              }
              Actions proposed_actions;
              proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(del_digit1, digit1)));
              proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(del_digit2, digit2)));
              return Step(*this, vague_hint, hint, difficulty, proposed_actions, points);
            }
          }
        }
      }
    }
    return Step();
  }

} // namespace Sudoku
