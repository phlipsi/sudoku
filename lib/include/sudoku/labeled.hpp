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

#ifndef __LABELED_HPP
#define __LABELED_HPP

#include <string>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace Sudoku {

  class Labeled {
  public:
    typedef boost::uuids::uuid HashType;
  
    Labeled(const std::string& name,
            const std::string& description,
            const std::string& author,
            HashType base)
      : name(name),
        description(description),
        author(author),
        hash(calc_hash(base)) { }

    virtual ~Labeled() { }
    
    const std::string& get_name() const { return name; }
    const std::string& get_description() const { return description; }
    const std::string& get_author() const { return author; }
    const HashType& get_hash() const { return hash; }
    
    bool operator < (const Labeled& x) const {
      return hash < x.hash;
    }

  protected:
    HashType nil_hash() const {
      return boost::uuids::nil_generator()();
    }
    
  private:
    std::string name;
    std::string description;
    std::string author;
    HashType hash;

    HashType calc_hash(HashType basis) const {
      std::string s;
      s.reserve(name.size() + description.size() + author.size());
      s.append(name);
      s.append(description);
      s.append(author);
      boost::uuids::name_generator gen(basis);
      return gen(s);
    }
  };

} // namespace Sudoku

#endif // __LABELED_HPP
