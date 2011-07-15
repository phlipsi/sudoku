#include <sudoku/generator.hpp>

#include <vector>
#include <algorithm>

#include <boost/array.hpp>

#include <sudoku/technique.hpp>
#include <sudoku/symmetry.hpp>
#include <sudoku/solver.hpp>
#include <sudoku/sudoku.hpp>
#include <sudoku/proceeding.hpp>

namespace Sudoku {

  namespace {

    struct Data {
      Technique::Difficulty difficulty;
      int min_score, max_score;
      int attempts;
      int set_digits;
      std::vector<Symmetry::const_iterator> symmetry_classes;
      Solver* solver;
    };

    // TODO: Sometimes the generator tries very early Sudoku fields too
    //       intensively. A different position might be better instead
    //       of trying all possible digits in a certain positions.
    //       This problem eats up computing time!
    bool generate_impl(Data& data, int current_symmetry, int last_pos, boost::array<int, 81>& field)
    {
      if (data.attempts == 0) {
        return false;
      }
      const int next_pos = next(*(data.symmetry_classes[current_symmetry]), last_pos);
      if (next_pos == -1) {
        // current symmetry class is filled
        if (data.set_digits < 17) {
          for (unsigned int next_symmetry = current_symmetry + 1; next_symmetry < data.symmetry_classes.size(); ++next_symmetry) {
            if (generate_impl(data, next_symmetry, -1, field)) {
              return true;
            }
          }
          return false;
        } else {
          Sudoku test(field);
          std::cout << data.attempts << ' ' << data.set_digits << ": ";
          for (unsigned int i = 0; i < 81; ++i) {
            std::cout << field[i];
          }
          std::cout.flush();
          const int solutions = test.count_solutions(2, 10000);
          --data.attempts;
          std::cout << " => " << solutions << std::endl;
          if (solutions == 0) {
            // No solutions => go back
            return false;
          } else if (solutions == 1) {
            Proceeding p;
            if (data.solver->solve(test, p)) {
              Technique::Difficulty diff = Technique::EASY;
              int score = 0;
              p.evaluate(diff, score);
              if (score > data.max_score || diff > data.difficulty) {
                // too difficult
                // => try all symmetry classes left by calling yourself
                //    recursively
                for (unsigned int next_symmetry = current_symmetry + 1; next_symmetry < data.symmetry_classes.size(); ++next_symmetry) {
                  if (generate_impl(data, next_symmetry, -1, field)) {
                    return true;
                  }
                }
                // Nothing found
                return false;
              }
              if (score <= data.max_score && score >= data.min_score && diff == data.difficulty) {
                // Congratulations! We found a sudoku satisfying our constraints
                return true;
              } else {
                // constraints aren't fulfilled and it isn't simply too difficult
                // => Go back, becaus we have to try other
                //    digits in our symmetry class or 
                //    a completely different symmetry class
                return false;
              }
            } else {
              // Isn't solvable... This shouldn't happen!
              return false;
            }
          } else {
            // not unique
            // => try all symmetry classes left by calling yourself
            for (unsigned int next_symmetry = current_symmetry + 1; next_symmetry < data.symmetry_classes.size(); ++next_symmetry) {
              if (generate_impl(data, next_symmetry, -1, field)) {
                return true;
              }
            }
            return false;
          }
        }
      } else {
        // We must fill our symmetry class at first!
        boost::array<bool, 9> allowed;
        allowed.assign(true);
        for (int j = 0; j < 81; ++j) {
          if (PROPER_PEERS[next_pos][j]) {
            const int d = field[j];
            if (d != 0) {
              allowed[d - 1] = false;
            }
          }
        }
        std::vector<int> possible_digits;
        possible_digits.reserve(9);
        for (int d = 0; d < 9; ++d) {
          if (allowed[d]) {
            possible_digits.push_back(d + 1);
          }
        }
        if (possible_digits.empty()) {
          return false;
        }
        std::random_shuffle(possible_digits.begin(), possible_digits.end());
        for (unsigned int j = 0; j < possible_digits.size(); ++j) {
          field[next_pos] = possible_digits[j];
          ++data.set_digits;
          // Call yourself recursively
          if (generate_impl(data, current_symmetry, next_pos, field)) {
            return true;
          }
          field[next_pos] = 0;
          --data.set_digits;
        }
        return false;
      }
    }
  
  }

  bool generate(Technique::Difficulty difficulty,
                int min_score, int max_score, int attempts,
                const Symmetry& symmetry,
                Solver& solver,
                Sudoku& sudoku)
  {
    Data data;
    data.difficulty = difficulty;
    data.min_score = min_score;
    data.max_score = max_score;
    data.attempts = attempts;
    data.set_digits = 0;
    data.symmetry_classes.reserve(symmetry.count_classes());
    for (Symmetry::const_iterator i = symmetry.begin(); i != symmetry.end(); ++i) {
      data.symmetry_classes.push_back(i);
    }
    std::random_shuffle(data.symmetry_classes.begin(), data.symmetry_classes.end());
    data.solver = &solver;
    for (unsigned int j = 0; j < data.symmetry_classes.size(); ++j) {
      boost::array<int, 81> field;
      field.assign(0);
      if (generate_impl(data, j, -1, field)) {
        sudoku.assign(field);
        return true;
      }
    }
    return false;
  }

} // namespace Sudoku
