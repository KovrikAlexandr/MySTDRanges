#pragma once

namespace my_std {

template <typename T, typename U>
struct is_same : std::false_type {};

template <typename T>
struct is_same<T, T> : std::true_type {};

template <typename T, typename U>
const bool is_same_v = is_same<T, U>::value;



template <typename T, typename = void>
struct has_iterator_type : std::false_type {};

template <typename T>
struct has_iterator_type<T, std::void_t<typename T::iterator> > : std::true_type {};

template <typename T>
const bool has_iterator_type_v = has_iterator_type<T>::value;



template <typename T, typename = void, typename = void>
struct has_operator_increment : std::false_type {};

template <typename T>
struct has_operator_increment
<
    T, 
    std::void_t<decltype(std::declval<T>().operator++())>
> : std::true_type {};

template <typename T>
const bool has_operator_increment_v = has_operator_increment<T>::value;



template <typename T, typename = void, typename = void>
struct has_operator_decrement : std::false_type {};

template <typename T>
struct has_operator_decrement
<
    T, 
    std::void_t<decltype(std::declval<T>().operator--())>
> : std::true_type {};

template <typename T>
const bool has_operator_decrement_v = has_operator_decrement<T>::value;



template <typename T, typename = void, typename = void>
struct has_operator_equals_to : std::false_type {};

template <typename T>
struct has_operator_equals_to
<
    T,
    std::void_t<decltype(std::declval<T>().operator==())>
> : std::true_type {};

template <typename T>
const bool has_operator_equals_to_v = has_operator_equals_to<T>::value;



template <typename T, typename = void, typename = void>
struct has_operator_not_equals_to : std::false_type {};

template <typename T>
struct has_operator_not_equals_to
<
    T, 
    std::void_t<decltype(std::declval<T>().operator!=())>
> : std::true_type {};

template <typename T>
const bool has_operator_not_equals_to_v = has_operator_not_equals_to<T>::value;



template <typename T, typename = void, typename = void>
struct has_operator_dereference : std::false_type {};

template <typename T>
struct has_operator_dereference
<
    T, 
    std::void_t<decltype(std::declval<T>().operator*())>
> : std::true_type {};

template <typename T>
const bool has_operator_dereference_v = has_operator_dereference<T>::value;



template <typename T, typename = void>
struct has_operator_plus : std::false_type {};

template <typename T>
struct has_operator_plus <
    T, 
    std::void_t<decltype(std::declval<T>().operator+())>
> : std::true_type {};

template <typename T>
const bool has_operator_plus_v = has_operator_plus<T>::value;



template <typename T, typename = void>
struct has_operator_minus : std::false_type {};

template <typename T>
struct has_operator_minus <
    T, 
    std::void_t<decltype(std::declval<T>().operator-())>
> : std::true_type {};

template <typename T>
const bool has_operator_minus_v = has_operator_minus<T>::value;


template <typename T>
struct is_pair : std::false_type {};

template <typename U, typename V>
struct is_pair< std::pair<U, V> > : std::true_type {};

template <typename T>
const bool is_pair_v = is_pair<T>::value;

template <typename _Iter>
const bool is_input_iterator_v =   has_operator_increment_v<_Iter> || 
                                        has_operator_equals_to_v<_Iter> ||
                                        has_operator_not_equals_to_v<_Iter> ||
                                        has_operator_dereference_v<_Iter>;

template <typename _Iter>
const bool is_forward_iterator = is_input_iterator_v<_Iter>;

template <typename _Iter>
const bool is_bidirectional_iterator_v = is_forward_iterator<_Iter> || has_operator_decrement_v<_Iter>;

template <typename _Iter>
const bool is_random_access_iterator_v =    is_bidirectional_iterator_v<_Iter> || 
                                            has_operator_plus_v<_Iter> || 
                                            has_operator_minus_v<_Iter>;


template <typename C, typename = void>
struct has_begin_method : std::false_type {};

template <typename C>
struct has_begin_method<C, std::void_t<decltype(std::declval<C>().begin())>> : std::true_type {};

template <typename C>
const bool has_begin_method_v = has_begin_method<C>::value;



template <typename C, typename = void>
struct has_end_method : std::false_type {};

template <typename C>
struct has_end_method<C, std::void_t<decltype(std::declval<C>().end())>> : std::true_type {};

template <typename C>
const bool has_end_method_v = has_end_method<C>::value;

}