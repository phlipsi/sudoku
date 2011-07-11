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
      result.add_symmetry(p, false);
    }
    result.normalize();
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
        result.add_symmetry(p, false);
      }
    }
    result.normalize();
    return Symmetry(result);
  }

  // const Symmetry ROTATION_90             = Symmetry(1 << 0);
  // const Symmetry ROTATION_180            = Symmetry(1 << 1);
  const Symmetry HORIZONTAL_REFLECTION   = init_horizontal_reflection();
  const Symmetry VERTICAL_REFLECTION     = init_vertical_reflection();
  // const Symmetry DIAGONAL_REFLECTION     = Symmetry(1 << 4);
  // const Symmetry ANTIDIAGONAL_REFLECTION = Symmetry(1 << 5);

} // namespace Sudoku
