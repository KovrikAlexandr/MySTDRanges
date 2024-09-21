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
class key_iterator;

// Input iterator
template <typename _Iter>
class key_iterator<_Iter, std::input_iterator_tag> {
public:
    typedef decltype(std::declval<_Iter>().operator*().first) value_type;

    key_iterator(_Iter it)
        :   _it(it)
    {}

    key_iterator(const key_iterator& other)
        :   _it(other._it)
    {}

    key_iterator& operator++() {
        _it++;
        return *this;
    }

    key_iterator operator++(int) {
        key_iterator tmp(*this);
        _it++;
        return tmp;
    }

    bool operator==(const key_iterator& other) const { 
        return _it == other._it; 
    }

    bool operator!=(const key_iterator& other) const { 
        return _it != other._it; 
    }

    value_type operator*() { 
        return (*_it).first; 
    }

protected:
    _Iter _it;
};

// Forward iterator
template <typename _Iter>
class key_iterator<_Iter, std::forward_iterator_tag> : 
    public key_iterator<_Iter, std::input_iterator_tag>
{
public:
    typedef key_iterator<_Iter, std::input_iterator_tag> base_type;

    key_iterator(_Iter it)
        :   base_type(it)
    {}

    key_iterator(const key_iterator& other) = default;
};

// Bidirectional iterator
template <typename _Iter>
    requires (
        my_std::has_operator_decrement_v<_Iter>
    )
class key_iterator<_Iter, std::bidirectional_iterator_tag> : 
    public key_iterator<_Iter, std::forward_iterator_tag> 
{   
public:
    typedef key_iterator<_Iter, std::forward_iterator_tag> base_type;
    using base_type::_it;

    key_iterator(_Iter it)
        :  base_type(it)
    {}

    key_iterator& operator--() {
        _it--;
        return *this;
    }

    key_iterator operator--(int) {
        key_iterator tmp(*this);
        _it--;
        return tmp;
    }
};

// Random access iterator
template <typename _Iter>
class key_iterator<_Iter, std::random_access_iterator_tag> : 
    public key_iterator<_Iter, std::bidirectional_iterator_tag> 
{   
public:
    typedef key_iterator<_Iter, std::bidirectional_iterator_tag> base_type;
    key_iterator(_Iter it)
        :   base_type(it)
    {}
};

}

template <typename _Iter>
struct std::iterator_traits< my_std::key_iterator<_Iter, std::input_iterator_tag> > {
    typedef size_t difference_type;
    typedef decltype(std::declval<_Iter>().operator*().first) value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::input_iterator_tag iterator_category;
};

template <typename _Iter>
struct std::iterator_traits< my_std::key_iterator<_Iter, std::forward_iterator_tag> > {
    typedef size_t difference_type;
    typedef decltype(std::declval<_Iter>().operator*().first) value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::forward_iterator_tag iterator_category;
};

template <typename _Iter>
struct std::iterator_traits< my_std::key_iterator<_Iter, std::bidirectional_iterator_tag> > {
    typedef size_t difference_type;
    typedef decltype(std::declval<_Iter>().operator*().first) value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::bidirectional_iterator_tag iterator_category;
};

template <typename _Iter>
struct std::iterator_traits< my_std::key_iterator<_Iter, std::random_access_iterator_tag> > {
    typedef size_t difference_type;
    typedef decltype(std::declval<_Iter>().operator*().first) value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::random_access_iterator_tag iterator_category;
};




