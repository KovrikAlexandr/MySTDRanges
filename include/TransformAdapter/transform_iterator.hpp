#pragma once

#include <iterator>
#include <functional>

#include "my_type_traits.hpp"

template <typename _Iter, typename _IteratorCategory>
    requires (
        my_std::has_operator_increment_v<_Iter> ||
        my_std::has_operator_dereference_v<_Iter> ||
        my_std::has_operator_equals_to_v<_Iter> ||
        my_std::has_operator_not_equals_to_v<_Iter>
    )
class transform_iterator;

// Input iterator
template <typename _Iter>
class transform_iterator<_Iter, std::input_iterator_tag> {
public:
    typedef typename _Iter::value_type value_type;
    typedef std::function<value_type(value_type)> function_type;

    transform_iterator(_Iter it, function_type func)
        :   _it(it),
            _func(func)
    {}

    transform_iterator(const transform_iterator& other)
        :   _it(other._it),
            _func(other._func)
    {}

    transform_iterator& operator++() {
        _it++;
        return *this;
    }

    transform_iterator operator++(int) {
        transform_iterator tmp(*this);
        _it++;
        return tmp;
    }

    bool operator==(const transform_iterator& other) const { return _it == other._it; }

    bool operator!=(const transform_iterator& other) const { return _it != other._it; }

    value_type operator*() { return _func(*_it); }

protected:
    _Iter _it;
    function_type _func;
};

template <typename _Iter>
struct std::iterator_traits< transform_iterator<_Iter, std::input_iterator_tag> > {
    typedef size_t difference_type;
    typedef typename _Iter::value_type value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::input_iterator_tag iterator_category;
};

// Forward iterator
template <typename _Iter>
class transform_iterator<_Iter, std::forward_iterator_tag> : 
    public transform_iterator<_Iter, std::input_iterator_tag>
{
public:
    typedef transform_iterator<_Iter, std::input_iterator_tag> base_type;
    using typename base_type::function_type;

    transform_iterator(_Iter it, function_type func)
        :   base_type(it, func)
    {}
};

template <typename _Iter>
struct std::iterator_traits< transform_iterator<_Iter, std::forward_iterator_tag> > {
    typedef size_t difference_type;
    typedef typename _Iter::value_type value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::forward_iterator_tag iterator_category;
};

// Bidirectional iterator
template <typename _Iter>
    requires (
        my_std::has_operator_decrement_v<_Iter>
    )
class transform_iterator<_Iter, std::bidirectional_iterator_tag> : 
    public transform_iterator<_Iter, std::forward_iterator_tag> 
{   
public:
    typedef transform_iterator<_Iter, std::forward_iterator_tag> base_type;
    using base_type::_it;
    using typename base_type::function_type;

    transform_iterator(_Iter it, function_type func)
        :  base_type(it, func)
    {}

    transform_iterator& operator--() {
        _it--;
        return *this;
    }

    transform_iterator operator--(int) {
        transform_iterator tmp(*this);
        _it--;
        return tmp;
    }
};

template <typename _Iter>
struct std::iterator_traits< transform_iterator<_Iter, std::bidirectional_iterator_tag> > {
    typedef size_t difference_type;
    typedef typename _Iter::value_type value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::bidirectional_iterator_tag iterator_category;
};

// Random access iterator
template <typename _Iter>
class transform_iterator<_Iter, std::random_access_iterator_tag> : 
    public transform_iterator<_Iter, std::bidirectional_iterator_tag> 
{   
public:
    typedef transform_iterator<_Iter, std::bidirectional_iterator_tag> base_type;
    using typename base_type::function_type;
    transform_iterator(_Iter it, function_type func)
        :   base_type(it, func)
    {}
};

template <typename _Iter>
struct std::iterator_traits< transform_iterator<_Iter, std::random_access_iterator_tag> > {
    typedef size_t difference_type;
    typedef typename _Iter::value_type value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::random_access_iterator_tag iterator_category;
};


