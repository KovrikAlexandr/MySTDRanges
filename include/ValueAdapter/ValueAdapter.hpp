#pragma once

#include <functional>

#include "value_iterator.hpp"

namespace my_std {

template <typename _Container>
    requires (
        my_std::has_begin_method_v<_Container> ||
        my_std::has_end_method_v<_Container> ||
        my_std::has_iterator_type_v<_Container> ||
        my_std::is_pair_v<decltype(std::declval<typename _Container::iterator>().operator*())>
    )
class ValueAdapter {
public:
    typedef _Container                          container_type;
    typedef typename container_type::iterator   container_iterator;
    typedef decltype(std::declval<typename _Container::iterator>().operator*().second)   value_type;


    typedef value_iterator<
        container_iterator,
        typename std::iterator_traits<container_iterator>::iterator_category>
    iterator;

    ValueAdapter(container_type& container)
        :   _begin(container.begin()),
            _end(container.end())
    {}

    iterator begin() { 
        return _begin; 
    }

    iterator end() { 
        return _end; 
    }

private:
    container_iterator _begin;
    container_iterator _end;
};


struct ValueTag {};

ValueTag value() {
    return ValueTag(); 
}

template <typename _Container>
ValueAdapter<_Container> operator|(_Container& cont, ValueTag) {
    return ValueAdapter(cont);
}

template <typename _Container>
ValueAdapter<_Container> operator|(_Container&& cont, ValueTag) {
    return ValueAdapter(cont);
}

}