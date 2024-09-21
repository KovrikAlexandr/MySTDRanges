#pragma once

#include <iterator>

#include "my_type_traits.hpp"

namespace my_std {

template <typename _Iter>
    requires (
        my_std::has_operator_increment_v<_Iter> ||
        my_std::has_operator_decrement_v<_Iter> ||
        my_std::has_operator_dereference_v<_Iter> ||
        my_std::has_operator_equals_to_v<_Iter> ||
        my_std::has_operator_not_equals_to_v<_Iter> ||
        my_std::has_operator_dereference_v<_Iter>
    )
class reverse_iterator {
public:
    typedef typename _Iter::value_type value_type;

    reverse_iterator(_Iter it)
        : _it(it)
    {}

    reverse_iterator(const reverse_iterator& other)
        : _it(other._it)
    {}

    reverse_iterator& operator++() {
        --_it;
        return *this;
    }

    reverse_iterator operator++(int) {
        reverse_iterator tmp(*this);
        --_it;
        return tmp;
    }

    reverse_iterator& operator--() {
        ++_it;
        return *this;
    }

    reverse_iterator operator--(int) {
        reverse_iterator tmp(*this);
        ++_it;
        return tmp;
    }

    value_type operator*() const {
        auto tmp = _it;
        return *(--tmp);
    }

    bool operator==(const reverse_iterator& other) const {
        return _it == other._it;
    }

    bool operator!=(const reverse_iterator& other) const {
        return _it != other._it;
    }

private:
    _Iter _it;
};

}

template <typename _Iter>
struct std::iterator_traits<my_std::reverse_iterator<_Iter>> {
    typedef size_t difference_type;
    typedef typename _Iter::value_type value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::bidirectional_iterator_tag iterator_category;
};