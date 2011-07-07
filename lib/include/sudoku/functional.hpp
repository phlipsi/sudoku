// libsudoku
//
// Copyright 2011 Philipp Wähnert <phil.wnrt@googlemail.com>
//
// libsudoku is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.

#ifndef __FUNCTIONAL_HPP
#define __FUNCTIONAL_HPP

/**
 * @file functional.hpp
 * @brief Templates aren't provided by the STL Functional library
 */

#include <functional>

namespace Sudoku {
  
  /**
   * @brief Templated functor for the logical xor operation,
   *        same as <tt>std::logical_and</tt>
   * @tparam T type of the input values \c x and \c y
   */
  template<typename T>
  struct logical_xor : public std::binary_function<T, T, bool> {
    bool operator() (const T& x, const T& y) { return (x && !y) || (!x && y); }
  };
  
  /**
   * @brief Templated functor for the <tt>\<\<</tt> operator
   * @tparam S type of the lhs
   * @tparam T type of the rhs
   */
  template<typename S, typename T>
  struct inserter : public std::binary_function<S&, T, S&> {
    S& operator() (S& s, T t) const { s << t; return s; }
  };
  
  // template<typename S, typename T>
  // struct inserter : std::unary_function<T, void> {
  //   S& s;
  //   inserter(S& _s) : s(_s) { }
  //   void operator() (T t) const { s << t; }
  // };
  
  template<typename T>
  struct shifter : public std::unary_function<T, T> {
    const T length;
    const T shift;
    shifter(T alength, T ashift) : length(alength), shift(ashift) { }
    T operator() (T t) const { return (t + shift) % length; }
  };
  
  template<typename T>
  struct transposition : public std::unary_function<T, T> {
    const T arg;
    const T value;
    transposition(T aarg, T avalue) : arg(aarg), value(avalue) { }
    T operator() (T t) const {
      return t == arg ? value : (t == value ? arg : t );
    }
  };
  
  template<typename U, typename V>
  struct unary_compose
    : public std::unary_function<typename V::argument_type,
                                 typename U::result_type> {
    U op1;
    V op2;
    unary_compose(U _op1, V _op2) : op1(_op1), op2(_op2) { }
    typename U::result_type operator() (typename V::argument_type arg) {
      return op1(op2(arg));
    }
  };
  
} // namespace Sudoku

#endif // __FUNCTIONAL_HPP
