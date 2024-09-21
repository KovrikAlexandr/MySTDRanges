#pragma once

#include <functional>
#include <iterator>

namespace my_std {

struct DropHolder {
    DropHolder(size_t drop) 
        : _drop(drop)
    {}
    size_t _drop;
};

DropHolder drop(size_t drop) { return DropHolder(drop); }

template <typename _Container>
    requires (
        my_std::has_begin_method_v<_Container> ||
        my_std::has_end_method_v<_Container> ||
        my_std::has_iterator_type_v<_Container> ||
        my_std::is_random_access_iterator_v<typename _Container::iterator>
    )
class DropAdapter {
public:
    typedef _Container                              container_type;
    typedef typename container_type::value_type     value_type;
    typedef typename container_type::iterator       iterator;

    DropAdapter(container_type& container, size_t drop)
        :   _begin(container.begin() + drop),
            _end(container.end())
    {}

    DropAdapter(const DropAdapter& other) = default;

    iterator begin() { 
        return _begin; 
    }

    iterator end() { 
        return _end; 
    }

private:
    iterator _begin;
    iterator _end;
};

template <typename _Container>
DropAdapter<_Container> operator|(_Container& cont, DropHolder drop) {
    return DropAdapter(cont, drop._drop);
}

template <typename _Container>
DropAdapter<_Container> operator|(_Container&& cont, DropHolder drop) {
    return DropAdapter(cont, drop._drop);
}

}