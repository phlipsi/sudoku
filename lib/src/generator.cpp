#include <sudoku/generator.hpp>

#include <vector>
#include <algorithm>

#include <boost/array.hpp>

#include <sudoku/plainfield.hpp>
#include <sudoku/solver.hpp>
#include <sudoku/sudoku.hpp>
#include <sudoku/symmetry.hpp>

namespace Sudoku {

  namespace {
    
    bool generate_full_impl(int last, boost::array<int, 81>& field) {
      if (last == 80) {
        return true;
      }
      
      const int next = last + 1;
      boost::array<bool, 9> allowed;
      allowed.assign(true);
      for (int i = 0; i < 81; ++i) {
        if (PROPER_PEERS[next][i]) {
          const int digit = field[i];
          if (digit != 0) {
            allowed[digit - 1] = false;
          }
        }
      }
      std::vector<int> allowed_digits;
      allowed_digits.reserve(9);
      for (int d = 0; d < 9; ++d) {
        if (allowed[d]) {
          allowed_digits.push_back(d + 1);
        }
      }
      std::random_shuffle(allowed_digits.begin(), allowed_digits.end());
      for (unsigned int i = 0; i < allowed_digits.size(); ++i) {
        field[next] = allowed_digits[i];
        if (generate_full_impl(next, field)) {
          return true;
        }
      }
      field[next] = 0;
      return false;
    }
    
  }

  Sudoku generate_full() {
    boost::array<int, 81> field;
    field.assign(0);
    if (generate_full_impl(-1, field)) {
      return Sudoku(field);
    } else {
      return Sudoku();
    }
  }

  namespace {
    
    struct Data {
      const boost::array<int, 81>& original_field;
      boost::array<int, 81>& field;
      const Step::Difficulty difficulty;
      const int min_score;
      const int max_score;
      int max_fails;
      int unique_fails;
      int unsolvable_fails;
      int too_difficult_fails;
      const std::vector<Symmetry::const_iterator>& symmetry_classes;
      Solver& solver;
    };
    
    bool generate_impl(Data& data, int next_symmetry) {
      if (!unique(data.field)) {
        ++data.unique_fails;
        return false;
      }
      const Proceeding p = data.solver.solve(Sudoku(data.field), data.difficulty, data.max_score, true);
      if (!p.is_solved()) {
        ++data.unsolvable_fails;
        return false;
      }
      Step::Difficulty max_diff;
      int score = 0;
      p.evaluate(max_diff, score);
      if (score > data.max_score || max_diff > data.difficulty) {
        ++data.too_difficult_fails;
        return false;
      }
      if (score >= data.min_score && score <= data.max_score && max_diff == data.difficulty) {
        return true;
      }
      for (unsigned int i = next_symmetry; i < data.symmetry_classes.size(); ++i) {
        const Positions& symmetry_class = *(data.symmetry_classes[i]);
        for (int j = 0; j < 81; ++j) {
          if (symmetry_class[j]) {
            data.field[j] = 0;
          }
        }
        if (generate_impl(data, i + 1)) {
          return true;
        }
        if (data.unique_fails + data.unsolvable_fails + data.too_difficult_fails >= data.max_fails) {
          return false;
        }
        for (int j = 0; j < 81; ++j) {
          if (symmetry_class[j]) {
            data.field[j] = data.original_field[j];
          }
        }
      }
      return false;
    }
    
  }

  Info generate(Step::Difficulty difficulty,
                int min_score, int max_score,
                int max_fails,
                const Symmetry& symmetry,
                Solver& solver,
                Sudoku& sudoku) {
    boost::array<int, 81> original_field;
    original_field.assign(0);

    if (generate_full_impl(-1, original_field)) {
      boost::array<int, 81> field = original_field;
      
      std::vector<Symmetry::const_iterator> symmetry_classes;
      for (Symmetry::const_iterator i = symmetry.begin(); i != symmetry.end(); ++i) {
        symmetry_classes.push_back(i);
      }
      std::random_shuffle(symmetry_classes.begin(), symmetry_classes.end());
  
      Data data = { original_field, field, difficulty, min_score, max_score, max_fails, 0, 0, 0, symmetry_classes, solver };
      const bool result = generate_impl(data, 0);
      if (result) {
        sudoku = Sudoku(field);
        return Info(true, data.unique_fails, data.unsolvable_fails, data.too_difficult_fails);
      } else {
        sudoku = Sudoku();
        return Info(false, data.unique_fails, data.unsolvable_fails, data.too_difficult_fails);
      }
    }
    
    sudoku = Sudoku();
    return Info(false, 0, 0, 0);
  }
} // namespace Sudoku
