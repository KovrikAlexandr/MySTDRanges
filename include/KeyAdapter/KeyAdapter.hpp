#pragma once

#include <functional>

#include "key_iterator.hpp"

namespace my_std {

template <typename _Container>
    requires (
        my_std::has_begin_method_v<_Container> ||
        my_std::has_end_method_v<_Container> ||
        my_std::has_iterator_type_v<_Container> ||
        my_std::is_pair_v<decltype(std::declval<typename _Container::iterator>().operator*())>
    )
class KeyAdapter {
public:
    typedef _Container                          container_type;
    typedef typename container_type::iterator   container_iterator;
    typedef decltype(std::declval<typename _Container::iterator>().operator*().first)   value_type;

    typedef key_iterator<
        container_iterator,
        typename std::iterator_traits<container_iterator>::iterator_category>
    iterator;

    KeyAdapter(container_type& container)
        :   _begin(container.begin()),
            _end(container.end())
    {}

    iterator begin() { return iterator(_begin); }

    iterator end() { return iterator(_end); }

private:
    container_iterator _begin;
    container_iterator _end;
};


struct KeyTag {};

KeyTag key() {
    return KeyTag(); 
}

template <typename _Container>
KeyAdapter<_Container> operator|(_Container& cont, KeyTag) {
    return KeyAdapter(cont);
}

template <typename _Container>
KeyAdapter<_Container> operator|(_Container&& cont, KeyTag) {
    return KeyAdapter(cont);
}

}