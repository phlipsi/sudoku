#ifndef __PLAINFIELD_HPP
#define __PLAINFIELD_HPP

#include <list>

#include <boost/array.hpp>

namespace Sudoku {

  int solutions(const boost::array<int, 81>& plain_field, int max, std::list< boost::array<int, 81> >& solutions);
  bool unique(const boost::array<int, 81>& plain_field);

} // namespace Sudoku

#endif // __PLAINFIELD_HPP
