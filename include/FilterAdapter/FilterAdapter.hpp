#pragma once

#include <functional>

#include "my_type_traits.hpp"

namespace my_std {

template <typename _Container>
    requires (
        my_std::has_begin_method_v<_Container> ||
        my_std::has_end_method_v<_Container> ||
        my_std::has_iterator_type_v<_Container> ||
        my_std::is_bidirectional_iterator_v<typename _Container::iterator>
    )
class FilterAdapter {
public:
    typedef _Container                              container_type;
    typedef typename container_type::value_type     value_type;
    typedef std::function<bool(value_type)>         func_type;
    typedef typename container_type::iterator       container_iterator;
    
    typedef FilterAdapter iterator;

    FilterAdapter(container_type& container, func_type filter_filter)
        :   _filter(filter_filter), 
            _begin(container.begin()),
            _end(container.end()),
            _current(container.end())
    {
        if (!_filter(*_begin)) { ++_begin; }
    }

    FilterAdapter& operator++() {
        do { _current++; } while (!_filter(*_current) && _current != _end);
        return (*this);
    }

    FilterAdapter operator++(int i) {
        FilterAdapter tmp(*this);
        do { _current++; } while (!_filter(*_current) && _current != _end);
        return tmp;
    }

    FilterAdapter& operator--() {
        do {
             --_current; 
        } while (!_filter(_current));
        return (*this);
    }

    FilterAdapter operator--(int i) {
        FilterAdapter tmp(*this);
        --(*this);
        return tmp;
    }

    value_type operator*() {
        return *_current; 
    }

    bool operator==(const FilterAdapter& other) const {
        return _begin == other._begin && _end == other._end;
    }

    bool operator!=(const FilterAdapter& other) const {
        return _begin != other._begin || _end != other._end;
    }

    iterator begin() { 
        return FilterAdapter(_begin, _end, _begin, _filter); 
    }

    iterator end() { 
        return FilterAdapter(_begin, _end, _end, _filter); 
    }

private:
    container_iterator _begin;
    container_iterator _end;
    container_iterator _current;
    func_type _filter;

    FilterAdapter(container_iterator b, container_iterator e, container_iterator c, func_type f) 
        :   _begin(b),
            _end(e),
            _current(c),
            _filter(f)
    {}
};


template <typename T>
struct FilterFuncHolder {
    FilterFuncHolder(std::function<bool(T)> func) 
        : _filter(func)
    {}
    std::function<bool(T)> _filter;
};


template <typename T>
FilterFuncHolder<T> filter(std::function<bool(T t)> func) { 
    return FilterFuncHolder<T>(func); 
}


template <typename Func>
auto filter(Func f) { 
    return filter(std::function(f)); 
}


template <typename _Container, typename T>
FilterAdapter<_Container> operator|(_Container& cont, FilterFuncHolder<T> func) {
    return FilterAdapter(cont, func._filter);
}


template <typename _Container, typename T>
FilterAdapter<_Container> operator|(_Container&& cont, FilterFuncHolder<T> func) {
    return FilterAdapter(cont, func._filter);
}

}

template <typename _Cont>
struct std::iterator_traits< my_std::FilterAdapter<_Cont> > {
    typedef size_t difference_type;
    typedef typename _Cont::value_type value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::bidirectional_iterator_tag iterator_category;
};