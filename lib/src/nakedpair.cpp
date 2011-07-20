#include <sudoku/nakedpair.hpp>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <sudoku/action.hpp>
#include <sudoku/common_actions.hpp>
#include <sudoku/sudoku.hpp>

namespace Sudoku {

  Step NakedPair::do_try_technique(const Sudoku& sudoku) {
    for (int k = 0; k < 9; ++k) {
      int box_index1 = first(BOXES[k]);
      for (int i = 0; i < 9; ++i) {
        {
          const Pencilmarks& p1 = sudoku.get_pencilmarks(9 * k + i);
          if (count(p1) == 2) {
            for (int j = i + 1; j < 9; ++j) {
              const Pencilmarks& p2 = sudoku.get_pencilmarks(9 * k + j);
              if (p1 == p2) {
                const int d1 = first(p1);
                const int d2 = next(p1, d1);
                
                const int box = get_box(9 * k + i);
                if (box == get_box(9 * k + j)) {
                  const std::string vague_hint = "Locked pair";
                  const std::string hint = boost::str(boost::format("Locked pair %1%,%2% in row %3% and box %4%") % (d1 + 1) % (d2 + 1) % (k + 1) % (box + 1));
                  Actions proposed_actions;
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(ROWS[k], d1)));
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(ROWS[k], d2)));
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(BOXES[box], d1)));
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(BOXES[box], d2)));
                  const int points = 40;
                  return Step(*this, vague_hint, hint, Step::MODERATE, proposed_actions, points);
                } else {
                  const std::string vague_hint = "Naked pair";
                  const std::string hint = boost::str(boost::format("Naked pair %1%,%2% in row %3%") % (d1 + 1) % (d2 + 1) % (k + 1));
                  Actions proposed_actions;
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(ROWS[k], d1)));
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(ROWS[k], d2)));
                  const int points = 60;
                  return Step(*this, vague_hint, hint, Step::TOUGH, proposed_actions, points);
                }
              }
            }
          }
        }
        {
          const Pencilmarks& p1 = sudoku.get_pencilmarks(k + 9 * i);
          if (count(p1) == 2) {
            for (int j = i + 1; j < 9; ++j) {
              const Pencilmarks& p2 = sudoku.get_pencilmarks(k + 9 * j);
              if (p1 == p2) {
                const int d1 = first(p1);
                const int d2 = next(p1, d1);
                
                const int box = get_box(k + 9 * i);
                if (box == get_box(k + 9 * j)) {
                  const std::string vague_hint = "Locked pair";
                  const std::string hint = boost::str(boost::format("Locked pair %1%,%2% in column %3% and box %4%") % (d1 + 1) % (d2 + 1) % (k + 1) % (box + 1));
                  Actions proposed_actions;
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(COLS[k], d1)));
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(COLS[k], d2)));
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(BOXES[box], d1)));
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(BOXES[box], d2)));
                  const int points = 40;
                  return Step(*this, vague_hint, hint, Step::MODERATE, proposed_actions, points);
                } else {
                  const std::string vague_hint = "Naked pair";
                  const std::string hint = boost::str(boost::format("Naked pair %1%,%2% in column %3%") % (d1 + 1) % (d2 + 1) % (k + 1));
                  Actions proposed_actions;
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(COLS[k], d1)));
                  proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(COLS[k], d2)));
                  const int points = 60;
                  return Step(*this, vague_hint, hint, Step::TOUGH, proposed_actions, points);
                }
              }
            }
          }
        }
        {
          const Pencilmarks& p1 = sudoku.get_pencilmarks(box_index1);
          if (count(p1) == 2) {
            int box_index2 = next(BOXES[k], box_index1);
            for (int j = i + 1; j < 9; ++j) {
              const Pencilmarks& p2 = sudoku.get_pencilmarks(box_index2);
              if (p1 == p2) {
                const int d1 = first(p1);
                const int d2 = next(p1, d1);
                
                const std::string vague_hint = "Naked pair";
                const std::string hint = boost::str(boost::format("Naked pair %1%,%2% in box %3%") % (d1 + 1) % (d2 + 1) % (k + 1));
                Actions proposed_actions;
                proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(BOXES[k], d1)));
                proposed_actions.push_back(boost::shared_ptr<Action>(new DeletePencilMark(BOXES[k], d2)));
                const int points = 60;
                return Step(*this, vague_hint, hint, Step::TOUGH, proposed_actions, points);
              }
              box_index2 = next(BOXES[k], box_index2);
            }
          }
        }
        box_index1 = next(BOXES[k], box_index1);
      }
    }
    return Step();
  }

} // namespace Sudoku
