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

#ifndef __BOOLARRAY_HPP
#define __BOOLARRAY_HPP

#include <cstddef>
#include <algorithm>
#include <functional>

#include <boost/array.hpp>

#include "functional.hpp"

namespace Sudoku {

  template<std::size_t N, typename F>
  inline void transform(boost::array<bool, N>& a, const boost::array<bool, N>& b, F f) {
    std::transform(a.begin(), a.end(), b.begin(), a.begin(), f);
  }
  
  template<std::size_t N>
  inline void and_assign(boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    transform(a, b, std::logical_and<bool>());
  }

  template<std::size_t N>
  inline void or_assign(boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    transform(a, b, std::logical_or<bool>());
  }

  template<std::size_t N>
  inline void xor_assign(boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    transform(a, b, logical_xor<bool>());
  }

  template<std::size_t N>
  inline boost::array<bool, N> and_op(const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    boost::array<bool, N> result = a;
    and_assign(result, b);
    return result;
  }

  template<std::size_t N>
  inline boost::array<bool, N> or_op(const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    boost::array<bool, N> result = a;
    or_assign(result, b);
    return result;
  }

  template<std::size_t N>
  inline boost::array<bool, N> xor_op(const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    boost::array<bool, N> result = a;
    xor_assign(result, b);
    return result;
  }
  
  template<std::size_t N>
  inline boost::array<bool, N> not_op(const boost::array<bool, N>& a) {
    boost::array<bool, N> result;
    std::transform(a.begin(), a.end(), result.begin(), std::logical_not<bool>());
    return result;
  }

  template<std::size_t N>
  inline bool is_equal(const boost::array<bool, N>& a, bool value) {
    for (unsigned int i = 0; i < N; ++i) {
      if (a[i] != value) return false;
    }
    return true;    
  }
  
  template<std::size_t N>
  inline bool is_empty(const boost::array<bool, N>& a) {
    return is_equal(a, false);
  }
  
  template<std::size_t N>
  inline bool is_sole(const boost::array<bool, N>& a) {
    int count = 0;
    for (unsigned int i = 0; i < N; ++i) {
      if (a[i]) ++count;
      if (count > 1) return false;
    }
    return count == 1; // count might be zero
  }

  template<std::size_t N>
  bool is_sole(const boost::array<bool, N>& a,
               const boost::array<bool, N>& b,
               int& where)
  {
    where = -1;
    int counter = 0;
    for (int i = 0; i < 81; ++i) {
      if (a[i] && b[i]) {
        ++counter;
        where = i;
      }
      if (counter == 2) {
        where = -1;
        return false;
      }
    }
    return counter == 1;
  }

  template<std::size_t N>
  inline bool is_open(const boost::array<bool, N>& a) {
    int count = 0;
    for (unsigned int i = 0; i < N; ++i) {
      if (a[i]) ++count;
      if (count > 1) return true;
    }
    return false; // empty isn't open
  }    

  template<std::size_t N>
  inline int first(const boost::array<bool, N>& a) {
    for (unsigned int i = 0; i < N; ++i) {
      if (a[i]) return i;
    }
    return -1;
  }

  enum Compare { INCOMPARABLE, EQUAL, LESS, GREATER, LESS_OR_EQUAL, GREATER_OR_EQUAL };

  template<std::size_t N>
  inline Compare compare(const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    int left = 0;
    int right = 0;
    int equal = 0;
    for (unsigned int i = 0; i < N; ++i) {
      if (a[i] && !b[i]) {
        ++left;
      } else if (!a[i] && b[i]) {
        ++right;
      } else {
        ++equal;
      }
    }
    if (left > 0 && right > 0) {
      return INCOMPARABLE;
    } else if (left > 0) {
      if (equal > 0) {
        return GREATER_OR_EQUAL;
      } else {
        return GREATER;
      }
    } else if (right > 0) {
      if (equal > 0) {
        return LESS_OR_EQUAL;
      } else {
        return LESS;
      }
    } else {
      assert(left == 0);
      assert(right == 0);
      assert(equal == N);
      return EQUAL;
    }
  }
  
  /*bool operator < (const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    return compare(a, b) == LESS;
  }
  
  bool operator <= (const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    return compare(a, b) == LESS_OR_EQUAL;
  }
  
  bool operator == (const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    return compare(a, b) == EQUAL;
  }

  bool operator > (const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    return compare(a, b) == GREATER;
  }
  
  bool operator >= (const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    return compare(a, b) == GREATER_OR_EQUAL;
  }
  
  bool operator != (const boost::array<bool, N>& a, const boost::array<bool, N>& b) {
    const Compare c = compare(a, b);
    return c == LESS || c == GREATER;
  }*/

} // namespace Sudoku

#endif // __BOOLARRAY_HPP
