#include <sudoku/symmetry.hpp>

#include <sudoku/boolarray.hpp>

namespace Sudoku {

  void Symmetry::normalize() {
    EquiClasses new_equi_classes;
    
    for (EquiClasses::iterator a = equi_classes.begin(); a != equi_classes.end(); ++a) {
      Positions new_class;
      new_class.assign(false);
      
      Positions temp = *a;
      int j = first(temp);
      while (j != -1) {
        new_class[j] = true;
        
        EquiClasses::iterator b = a;
        ++b;
        while (b != equi_classes.end()) {
          if ((*b)[j]) {
            or_assign(temp, *b);
            and_assign(temp, not_op(new_class));
            b = equi_classes.erase(b);
          } else {
            ++b;
          }
        }
        
        temp[j] = false;
        j = first(temp);
      }
      
      new_equi_classes.push_back(new_class);
    }
    
    equi_classes = new_equi_classes;
  }

  Symmetry init_horizontal_reflection() {
    Symmetry result;
    for (int i = 0; i < 36; ++i) {
      Positions p;
      p.assign(false);
      p[i] = true;
      p[get_col(i) + 9 * (8 - get_row(i))] = true;
      result.add_symmetry(p);
    }
    return Symmetry(result);
  }

  Symmetry init_vertical_reflection() {
    Symmetry result;
    for (int col = 0; col < 4; ++col) {
      for (int row = 0; row < 9; ++row) {
        Positions p;
        p.assign(false);
        p[col + 9 * row] = true;
        p[8 - col + 9 * row] = true;
        result.add_symmetry(p);
      }
    }
    return Symmetry(result);
  }

  Symmetry init_rotation_180() {
    Symmetry result;
    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 9; ++col) {
        Positions p;
        p.assign(false);
        // (col, row) -> (8 - col, 8 - row)
        p[col + 9 * row] = true;
        p[8 - col + 9 * (8 - row)] = true;
        result.add_symmetry(p);
      }
    }
    return Symmetry(result);
  }

  Symmetry init_diagonal_relfection() {
    Symmetry result;
    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 9; ++col) {
        Positions p;
        p.assign(false);
        // (col, row) -> (row, col)
        p[col + 9 * row] = true;
        p[row + 9 * col] = true;
        result.add_symmetry(p);
      }
    }
    return Symmetry(result);
  }

  Symmetry init_antidiagonal_relfection() {
    Symmetry result;
    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 9; ++col) {
        Positions p;
        p.assign(false);
        // (col, row) -> (8 - row, 8 - col)
        p[col + 9 * row] = true;
        p[8 - row + 9 * (8 - col)] = true;
        result.add_symmetry(p);
      }
    }
    return Symmetry(result);
  }

  const Symmetry ROTATION_180            = init_rotation_180();
  const Symmetry HORIZONTAL_REFLECTION   = init_horizontal_reflection();
  const Symmetry VERTICAL_REFLECTION     = init_vertical_reflection();
  const Symmetry DIAGONAL_REFLECTION     = init_diagonal_relfection();
  const Symmetry ANTIDIAGONAL_REFLECTION = init_antidiagonal_relfection();

} // namespace Sudoku
