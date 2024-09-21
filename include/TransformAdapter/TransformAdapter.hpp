#pragma once

#include <functional>
#include <iterator>

#include "transform_iterator.hpp"
#include "my_type_traits.hpp"

namespace my_std {

template <typename T>
struct TransformFuncHolder {
    TransformFuncHolder(std::function<T(T)> func) 
        : _func(func)
    {}
    std::function<T(T)> _func;
};

template <typename _Container>
    requires (
        has_begin_method_v<_Container> ||
        has_end_method_v<_Container>
    )
class TransformAdapter {
public:
    typedef _Container                              container_type;
    typedef typename container_type::iterator       container_iterator;
    typedef typename container_type::value_type     value_type;
    typedef std::function<value_type(value_type)>   function_type;


    typedef transform_iterator< 
        typename container_type::iterator, 
        typename std::iterator_traits<typename container_type::iterator>::iterator_category> 
    iterator;

    TransformAdapter(container_type& container, function_type transform_func)
        :   _transform_func(transform_func),
            _begin(container.begin()),
            _end(container.end())
    {}

    iterator begin() { 
        return iterator(_begin, _transform_func); 
    }

    iterator end() { 
        return iterator(_end, _transform_func); 
    }

private:
    container_iterator _begin;
    container_iterator _end;
    function_type _transform_func;
};



template <typename T>
TransformFuncHolder<T> transform(std::function<T(T t)> func) {
    return TransformFuncHolder<T>(func);
}

template <typename Func>
auto transform(Func f) { 
    return transform(std::function(f)); 
}

template <typename _Container, typename T>
TransformAdapter<_Container> operator|(_Container& cont, TransformFuncHolder<T> fh) {
    return TransformAdapter(cont, fh._func);
}

template <typename _Container, typename T>
TransformAdapter<_Container> operator|(_Container&& cont, TransformFuncHolder<T> fh) {
    return TransformAdapter<_Container>(cont, fh._func);
}

}