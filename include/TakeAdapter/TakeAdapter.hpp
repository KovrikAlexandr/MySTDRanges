#pragma once

#include <functional>

#include "my_type_traits.hpp"

namespace my_std {

struct TakeHolder {
    TakeHolder(size_t take) 
        : _take(take)
    {}
    size_t _take;
};

TakeHolder take(size_t take) { return TakeHolder(take); }

template <typename _Container>
    requires (
        my_std::has_begin_method_v<_Container> ||
        my_std::has_end_method_v<_Container> ||
        my_std::has_iterator_type_v<_Container> ||
        my_std::is_random_access_iterator_v<typename _Container::iterator>
    )
class TakeAdapter {
public:
    typedef _Container container_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::iterator iterator;

    TakeAdapter(container_type& container, size_t take)
        :   _begin(container.begin()),
            _end(container.begin() + take)
    {}

    TakeAdapter(const TakeAdapter& other) = default;

    iterator begin() { return _begin; }

    iterator end() { return _end; }

private:
    iterator _begin;
    iterator _end;
};

template <typename _Container>
TakeAdapter<_Container> operator|(_Container& cont, TakeHolder take) {
    return TakeAdapter(cont, take._take);
}

template <typename _Container>
TakeAdapter<_Container> operator|(_Container&& cont, TakeHolder take) {
    return TakeAdapter(cont, take._take);
}

}