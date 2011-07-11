#ifndef __SYMMETRY_HPP
#define __SYMMETRY_HPP

#include <list>
#include <ostream>

#include <sudoku/boolarray.hpp>
#include <sudoku/positions.hpp>

namespace Sudoku {

  class Symmetry {
  public:
    typedef std::list<Positions> EquiClasses;
    typedef EquiClasses::const_iterator const_iterator;

    // No cell is symmetric to any other cell
    Symmetry() {
      Positions c;
      c.assign(false);
      c[0] = true;
      equi_classes.push_back(c);
      
      for (int i = 1; i < 81; ++i) {
        c[i - 1] = false;
        c[i] = true;
        equi_classes.push_back(c);
      }
    }
  
    int count_classes() const { return equi_classes.size(); }
    
    void add_symmetry(Positions c) {
      EquiClasses::iterator i = equi_classes.begin();
      while (i != equi_classes.end()) {
        const Positions& p = *i;
        bool common = false;
        for (int j = 0; j < 81; ++j) {
          if (p[j] && c[j]) {
            common = true;
            break;
          }
        }
        if (common) {
          or_assign(c, p);
          i = equi_classes.erase(i);
        } else {
          ++i;
        }
      }
      equi_classes.push_back(c);
    }

    void normalize();
    
    void join(const Symmetry& s) {
      for (EquiClasses::const_iterator i = s.equi_classes.begin(); i != s.equi_classes.end(); ++i) {
        add_symmetry(*i);
      }
    }

    void print(std::ostream& stream) const {
      for (EquiClasses::const_iterator i = equi_classes.begin(); i != equi_classes.end(); ++i) {
        stream << *i << '\n';
      }
    }

    const_iterator begin() const { return equi_classes.begin(); }
    const_iterator end() const { return equi_classes.end(); }
    
  private:
    EquiClasses equi_classes;
  };

  inline Symmetry join(const Symmetry& s, const Symmetry& t) {
    Symmetry result = s;
    result.join(t);
    return result;
  }

  extern const Symmetry ROTATION_90;
  extern const Symmetry ROTATION_180;
  extern const Symmetry HORIZONTAL_REFLECTION;
  extern const Symmetry VERTICAL_REFLECTION;
  extern const Symmetry DIAGONAL_REFLECTION;
  extern const Symmetry ANTIDIAGONAL_REFLECTION;

} // namespace Sudoku

#endif // __SYMMETRY_HPP
