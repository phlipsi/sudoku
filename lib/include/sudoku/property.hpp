#ifndef __PROPERTY_HPP
#define __PROPERTY_HPP

#include <functional>

namespace Sudoku {
  
  namespace Properties {

    template <class Result, class T>
    class MemberProperty {
    public:
      typedef T Type;
    
      explicit MemberProperty( Result (Type::*p)() const) : pmem(p) {}
      
      Result operator() (const Type& p) const { return (p.*pmem)(); }
    private:
      Result (Type::*pmem)() const;
    };
    
    template<typename Property, typename T, typename Relation>
    class PropertyRelation {
    public:
      typedef typename Property::Type Type;
    
      PropertyRelation(Property property, T value, Relation relation = Relation()) : property(property), value(value), relation(relation) { }
      
      bool operator () (const typename Property::Type& item) { return relation(property(item), value); }
    private:
      Property property;
      T value;
      Relation relation;
    };
    
    template<typename Property, typename T>
    PropertyRelation<Property, T, std::equal_to<T> > operator == (Property property, T value) {
      return PropertyRelation<Property, T, std::equal_to<T> >(property, value);
    }
    
    template<typename Property, typename T>
    PropertyRelation<Property, T, std::not_equal_to<T> > operator != (Property property, T value) {
      return PropertyRelation<Property, T, std::not_equal_to<T> >(property, value);
    }
    
    template<typename Property, typename T>
    PropertyRelation<Property, T, std::less<T> > operator < (Property property, T value) {
      return PropertyRelation<Property, T, std::less<T> >(property, value);
    }
    
    template<typename Property, typename T>
    PropertyRelation<Property, T, std::less_equal<T> > operator <= (Property property, T value) {
      return PropertyRelation<Property, T, std::less_equal<T> >(property, value);
    }
    
    template<typename Property, typename T>
    PropertyRelation<Property, T, std::greater<T> > operator > (Property property, T value) {
      return PropertyRelation<Property, T, std::greater<T> >(property, value);
    }
    
    template<typename Property, typename T>
    PropertyRelation<Property, T, std::greater_equal<T> > operator >= (Property property, T value) {
      return PropertyRelation<Property, T, std::greater_equal<T> >(property, value);
    }
    
    template<typename Property1, typename Property2, typename BinaryFunction>
    class PropertyBinaryFunction {
    public:
      typedef typename Property1::Type Type;
    
      PropertyBinaryFunction(Property1 property1, Property2 property2, BinaryFunction binary_function = BinaryFunction())
        : property1(property1), property2(property2), binary_function(binary_function) { }
      
      typename BinaryFunction::result_type operator () (const typename Property1::Type& item) {
        return binary_function(property1(item), property2(item));
      }
      
    private:
      Property1 property1;
      Property2 property2;
      BinaryFunction binary_function;
    };
    
    template<typename Property1, typename Property2>
    PropertyBinaryFunction<Property1, Property2, std::logical_and<bool> >
    operator && (Property1 property1, Property2 property2) {
      return PropertyBinaryFunction<Property1, Property2, std::logical_and<bool> >(property1, property2);
    }
    
    template<typename Property1, typename Property2>
    PropertyBinaryFunction<Property1, Property2, std::logical_or<bool> >
    operator || (Property1 property1, Property2 property2) {
      return PropertyBinaryFunction<Property1, Property2, std::logical_or<bool> >(property1, property2);
    }
    
    template<typename Property, typename UnaryFunction>
    class PropertyUnaryFunction {
    public:
      typedef typename Property::Type Type;
    
      PropertyUnaryFunction(Property property, UnaryFunction unary_function = UnaryFunction())
        : property(property), unary_function(unary_function) { }
      
      typename UnaryFunction::result_type operator () (const typename Property::Type& item) {
        return unary_function(property(item));
      }
      
    private:
      Property property;
      UnaryFunction unary_function;
    };
    
    template<typename Property>
    PropertyUnaryFunction<Property, std::logical_not<bool> >
    operator ! (Property property) {
      return PropertyUnaryFunction<Property, std::logical_not<bool> >(property);
    }
    
    template<typename InputIterator, typename OutputIterator, typename Property>
    void select(InputIterator source, InputIterator end, OutputIterator destination, Property property) {
      while (source != end) {
        *destination++ = property(*source++);
      }
    }
    
  } // namespace Properties

} // namespace Sudoku

#endif // __PROPERTY_HPP
