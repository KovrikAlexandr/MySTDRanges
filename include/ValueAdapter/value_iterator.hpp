#pragma once

#include <iterator>

#include "my_type_traits.hpp"

namespace my_std {

template <typename _Iter, typename _IteratorCategory>
    requires (
        my_std::has_operator_increment_v<_Iter> ||
        my_std::has_operator_dereference_v<_Iter> ||
        my_std::has_operator_equals_to_v<_Iter> ||
        my_std::has_operator_not_equals_to_v<_Iter> ||
        my_std::is_pair_v<decltype(std::declval<_Iter>().operator*())>
    )
class value_iterator;

// Input iterator
template <typename _Iter>
class value_iterator<_Iter, std::input_iterator_tag> {
public:
    typedef decltype(std::declval<_Iter>().operator*().second) value_type;

    value_iterator(_Iter it)
        :   _it(it)
    {}

    value_iterator(const value_iterator& other)
        :   _it(other._it)
    {}

    value_iterator& operator++() {
        _it++;
        return *this;
    }

    value_iterator operator++(int) {
        value_iterator tmp(*this);
        _it++;
        return tmp;
    }

    bool operator==(const value_iterator& other) const { 
        return _it == other._it; 
    }

    bool operator!=(const value_iterator& other) const { 
        return _it != other._it; 
    }

    value_type operator*() { 
        return (*_it).second; 
    }

protected:
    _Iter _it;
};

// Forward iterator
template <typename _Iter>
class value_iterator<_Iter, std::forward_iterator_tag> : 
    public value_iterator<_Iter, std::input_iterator_tag>
{
public:
    typedef value_iterator<_Iter, std::input_iterator_tag> base_type;

    value_iterator(_Iter it)
        :   base_type(it)
    {}
};

// Bidirectional iterator
template <typename _Iter>
    requires (
        my_std::has_operator_decrement_v<_Iter>
    )
class value_iterator<_Iter, std::bidirectional_iterator_tag> : 
    public value_iterator<_Iter, std::forward_iterator_tag> 
{   
public:
    typedef value_iterator<_Iter, std::forward_iterator_tag> base_type;
    using base_type::_it;

    value_iterator(_Iter it)
        :  base_type(it)
    {}

    value_iterator& operator--() {
        _it--;
        return *this;
    }

    value_iterator operator--(int) {
        value_iterator tmp(*this);
        _it--;
        return tmp;
    }
};

// Random access iterator
template <typename _Iter>
class value_iterator<_Iter, std::random_access_iterator_tag> : 
    public value_iterator<_Iter, std::bidirectional_iterator_tag> 
{   
public:
    typedef value_iterator<_Iter, std::bidirectional_iterator_tag> base_type;

    value_iterator(_Iter it)
        :   base_type(it)
    {}
};

}

template <typename _Iter>
struct std::iterator_traits< my_std::value_iterator<_Iter, std::input_iterator_tag> > {
    typedef size_t difference_type;
    typedef decltype(std::declval<_Iter>().operator*().second) value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::input_iterator_tag iterator_category;
};

template <typename _Iter>
struct std::iterator_traits< my_std::value_iterator<_Iter, std::forward_iterator_tag> > {
    typedef size_t difference_type;
    typedef decltype(std::declval<_Iter>().operator*().second) value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::forward_iterator_tag iterator_category;
};

template <typename _Iter>
struct std::iterator_traits< my_std::value_iterator<_Iter, std::bidirectional_iterator_tag> > {
    typedef size_t difference_type;
    typedef decltype(std::declval<_Iter>().operator*().second) value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::bidirectional_iterator_tag iterator_category;
};

template <typename _Iter>
struct std::iterator_traits< my_std::value_iterator<_Iter, std::random_access_iterator_tag> > {
    typedef size_t difference_type;
    typedef decltype(std::declval<_Iter>().operator*().second) value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::random_access_iterator_tag iterator_category;
};




