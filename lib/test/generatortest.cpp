#include <iostream>
#include <cstdlib>
#include <ctime>

#include <boost/timer.hpp>

#include <sudoku/generator.hpp>
#include <sudoku/sudoku.hpp>
#include <sudoku/step.hpp>

#include <sudoku/solver.hpp>
#include <sudoku/common_techniques.hpp>

#include <buildinfo.hpp>

const unsigned int N = 10;

int main() {
  srand(time(NULL));
  
  Sudoku::Solver solver;
  solver.append_technique(Sudoku::full_house);
  solver.append_technique(Sudoku::last_instance);
  solver.append_technique(Sudoku::hidden_row);
  solver.append_technique(Sudoku::hidden_column);
  solver.append_technique(Sudoku::hidden_box);
  solver.append_technique(Sudoku::naked_single);
  solver.append_technique(Sudoku::naked_pair);
  // solver.append_technique(Sudoku::back_tracking);

  Sudoku::Sudoku sudoku;
  boost::timer timer;

  std::cout << GIT_HEAD_SHA1 << '\n';
  for (unsigned int diff = Sudoku::Step::EASY; diff <= Sudoku::Step::UNFAIR; ++diff) {
    std::cout << "Difficulty: " << diff << '\n';
    int wins = 0;
    int score = 0;
    int steps = 0;

    int fails = 0;
    int unique_fails = 0;
    int unsolvable_fails = 0;
    int too_difficult_fails = 0;
    
    double time = 0.0;

    for (unsigned int k = 0; k < N; ++k) {
      timer.restart();
      Sudoku::Info info
        = Sudoku::generate(static_cast<Sudoku::Step::Difficulty>(diff), 300, 2000, 500,
                           // Sudoku::join(Sudoku::HORIZONTAL_REFLECTION, Sudoku::VERTICAL_REFLECTION),
                           // Sudoku::join(Sudoku::join(Sudoku::HORIZONTAL_REFLECTION, Sudoku::VERTICAL_REFLECTION), Sudoku::ROTATION_180),
                           // Sudoku::Symmetry(),
                           Sudoku::DIAGONAL_REFLECTION,
                           solver, sudoku);
      time += timer.elapsed();
      
      std::cout << '*';
      std::cout.flush();
      
      unique_fails += info.get_unique_fails();
      unsolvable_fails += info.get_unsolvable_fails();
      too_difficult_fails += info.get_too_difficult_fails();
      
      if (info) {
        ++wins;
        Sudoku::Proceeding p = solver.solve(sudoku, Sudoku::Step::TOUGH, 2000, true);
        int the_score;
        Sudoku::Step::Difficulty difficulty;
        p.evaluate(difficulty, the_score);
        score += the_score;
        steps += p.count_steps();
      } else {
        ++fails;
      }
    }
    
    for (unsigned int k = 0; k < N; ++k) {
      std::cout << static_cast<char>(0x08) << ' ' << static_cast<char>(0x08);
      
    }
    
    const double wins_ratio = static_cast<double>(wins) / static_cast<double>(N) * 100.0;
    const double score_ratio = static_cast<double>(score) / static_cast<double>(wins);
    const double steps_ratio = static_cast<double>(steps) / static_cast<double>(wins);

    const double fails_ratio = static_cast<double>(fails) / static_cast<double>(N) * 100.0;
    const double unique_fails_ratio = static_cast<double>(unique_fails) / static_cast<double>(N);
    const double unsolvable_fails_ratio = static_cast<double>(unsolvable_fails) / static_cast<double>(N);
    const double too_difficult_fails_ratio = static_cast<double>(too_difficult_fails) / static_cast<double>(N);

    std::cout << "Wins:\t\t"           << wins_ratio << "%\n"
              << "Avg. score:\t"       << score_ratio << '\n'
              << "Avg. steps:\t"       << steps_ratio << '\n'
              << "Fails:\t\t"          << fails_ratio << "%\n"
              << "Unique fails:\t"     << unique_fails_ratio << '\n'
              << "Unsolve fails:\t"    << unsolvable_fails_ratio << '\n'
              << "Too diff fails:\t"   << too_difficult_fails_ratio << '\n'
              << "Time:\t\t"           << time / static_cast<double>(N) << '\n' << std::endl;
  }
  
  return 0;
}
