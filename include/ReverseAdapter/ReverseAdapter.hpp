#pragma once

#include <functional>

#include "reverse_iterator.hpp"
#include "my_type_traits.hpp"

namespace my_std {

template <typename _Container>
    requires (
        my_std::has_begin_method_v<_Container> ||
        my_std::has_end_method_v<_Container> ||
        my_std::has_iterator_type_v<_Container> ||
        my_std::is_bidirectional_iterator_v<typename _Container::iterator>
    )
class ReverseAdapter {
public:
    typedef _Container container_type;
    typedef typename container_type::value_type value_type;

    typedef my_std::reverse_iterator<typename container_type::iterator> iterator;

    ReverseAdapter(container_type& container)
        : _container(container)
    {}

    iterator begin() { 
        return iterator(_container.end()); 
    }

    iterator end() { 
        return iterator(_container.begin()); 
    }

private:
    container_type& _container;
};


class Reverse {};

Reverse reverse() { 
    return Reverse(); 
}

template <typename _Container>
ReverseAdapter<_Container> operator|(_Container& cont, Reverse) {
    return ReverseAdapter<_Container>(cont);
}

template <typename _Container>
ReverseAdapter<_Container> operator|(_Container&& cont, Reverse) {
    return ReverseAdapter<_Container>(cont);
}

}

