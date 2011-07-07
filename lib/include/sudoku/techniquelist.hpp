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

#ifndef __TECHNIQUELIST_HPP
#define __TECHNIQUELIST_HPP

#include <algorithm>
#include <list>
#include <utility>

#include <sudoku/technique.hpp>

namespace Sudoku {

  class TechniqueList {
  public:
    typedef std::list< std::pair<bool, Technique*> > InternalList;
  
    class iterator {
    public:
      iterator() : iter() { }
      explicit iterator(InternalList::iterator iter) : iter(iter) { }
      
      bool& is_active() const { return iter->first; }
      Technique& operator * () const { return *(iter->second); }
      Technique* operator -> () const { return iter->second; }
      iterator& operator ++ () {
        ++iter;
        return *this;
      }
      iterator operator ++ (int) {
        iterator tmp(*this);
        ++*this;
        return tmp;
      }
      
      bool operator == (const iterator& i) const {
        return iter == i.iter;
      }
      
      bool operator != (const iterator& i) const {
        return iter != i.iter;
      }
      
      InternalList::iterator get_iterator() const { return iter; }
    private:
      InternalList::iterator iter;
    };
  
    class const_iterator {
    public:
      const_iterator() : iter() { }
      explicit const_iterator(InternalList::const_iterator iter) : iter(iter) { }
      explicit const_iterator(iterator i) : iter(i.get_iterator()) { }
      
      bool is_active() const { return iter->first; }
      const Technique& operator * () const { return *(iter->second); }
      const Technique* operator -> () const { return iter->second; }
      const_iterator& operator ++ () {
        ++iter;
        return *this;
      }
      const_iterator operator ++ (int) {
        const_iterator tmp(*this);
        ++*this;
        return tmp;
      }
      
      bool operator == (const const_iterator& i) const {
        return iter == i.iter;
      }
      
      bool operator != (const const_iterator& i) const {
        return iter != i.iter;
      }

      InternalList::const_iterator get_iterator() const { return iter; }
    private:
      InternalList::const_iterator iter;
    };
     
    void append_technique(Technique& t) {
      list.push_back(std::make_pair(true, &t));
    }
    
    iterator insert_technique(iterator position, Technique& t) {
      return iterator(list.insert(position.get_iterator(), std::make_pair(true, &t)));
    }
    
    iterator delete_technique(iterator position) {
      return iterator(list.erase(position.get_iterator()));
    }
    
    void reset_techniques() {
      for (iterator i = begin(); i != end(); ++i) {
        i->reset_counter();
      }
    }

    void clear_techniques() {
      list.clear();
    }
    
    void activate(iterator position, bool active = true) {
      position.get_iterator()->first = active;
    }

    const_iterator find_technique(const Technique::HashType& hash) const {
      return const_iterator(std::find_if(list.begin(), list.end(), HashIf(hash)));
    }
    
    iterator find_technique(const Technique::HashType& hash) {
      return iterator(std::find_if(list.begin(), list.end(), HashIf(hash)));
    }

    iterator begin() { return iterator(list.begin()); }
    iterator end() { return iterator(list.end()); }
    
    const_iterator begin() const { return const_iterator(list.begin()); }
    const_iterator end() const { return const_iterator(list.end()); }

  private:
    InternalList list;
    
    struct HashIf {
      HashIf(const Technique::HashType& hash) : hash(&hash) { }
      
      bool operator () (const std::pair<bool, const Technique*>& item) const {
        return item.second->get_hash() == *hash;
      }
      
      const Technique::HashType* hash;
    };
  };
  
} // namespace Sudoku

#endif // __TECHNIQUELIST_HPP
