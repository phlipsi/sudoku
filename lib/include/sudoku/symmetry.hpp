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
  
    // TODO: Make normalization local such that an insertion of a new
    //       equivalence class with following normalization is efficient.
    //       Thus: The Symmetry class is always normalized
    void add_symmetry(const Positions& c, bool do_normalize = true) {
      equi_classes.push_back(c);
      if (do_normalize) {
        normalize();
      }
    }
    
    void normalize();
    
    void join(const Symmetry& s) {
      EquiClasses cs = s.equi_classes;
      equi_classes.merge(cs);
      normalize();
    }

    void print(std::ostream& stream) const {
      for (EquiClasses::const_iterator i = equi_classes.begin(); i != equi_classes.end(); ++i) {
        // print(stream, *i);
        stream << *i << '\n';
      }
    }

    const_iterator begin() const { return equi_classes.begin(); }
    const_iterator end() const { return equi_classes.end(); }
    
  private:
    EquiClasses equi_classes;
  };


    /*Symmetry(unsigned long value = 0) : value(value) { }
    
    bool rotation_90() const { return value[0]; }
    bool rotation_180() const { return value[1]; }
    bool horizontal_reflection() const { return value[2]; }
    bool vertical_reflection() const { return value[3]; }
    bool diagonal_reflection() const { return value[4]; }
    bool antidiagonal_reflection() const { return value[5]; }

    std::set<int> associated_points(int i) const;

    void randomize() {
      for (int i = 0; i < 6; ++i) {
        value[i] = rand() > (RAND_MAX / 2);
      }
    }
    
    const Symmetry& operator &= (const Symmetry& s) {
      value &= s.value;
      return *this;
    }
    
    const Symmetry& operator |= (const Symmetry& s) {
      value |= s.value;
      return *this;
    }

    const Symmetry& operator ^= (const Symmetry& s) {
      value ^= s.value;
      return *this;
    }

    Symmetry operator ~ () const {
      Symmetry result;
      result.value = ~value;
      return result;
    }

    bool operator == (const Symmetry& s) const {
      return value == s.value;
    }

    bool operator != (const Symmetry& s) const {
      return value != s.value;
    }
    
  private:
    std::bitset<6> value;
  };

  inline Symmetry operator & (const Symmetry& s, const Symmetry& t) {
    Symmetry result = s;
    result &= t;
    return result;
  }

  inline Symmetry operator | (const Symmetry& s, const Symmetry& t) {
    Symmetry result = s;
    result |= t;
    return result;
  }
  
  inline Symmetry operator ^ (const Symmetry& s, const Symmetry& t) {
    Symmetry result = s;
    result ^= t;
    return result;
  }*/
  
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
