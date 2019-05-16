/**
 * @brief Набор не стандартных помошников определения типов
 * @author VKS
 */
#pragma once

#include <string>

///is_string

template<typename _T>
struct is_string : std::false_type {
};

template<>
struct is_string<std::string> : std::true_type {
};

///is_container

template<typename _T>
struct is_container : std::false_type {
};

template<typename ..._Args>
struct is_container<std::vector<_Args...>> : std::true_type {
};

template<typename ..._Args>
struct is_container<std::list<_Args...>> : std::true_type {
};

///are_same_type

template<typename ..._E>
struct are_same_type;

template<typename _E_lhs, typename _E_rhs, typename ..._E>
struct are_same_type<_E_lhs, _E_rhs, _E...> {
    static const bool value = std::is_same<_E_lhs, _E_rhs>::value && are_same_type<_E_rhs, _E...>::value;
};

template<typename _E_lhs, typename _E_rhs>
struct are_same_type<_E_lhs, _E_rhs> {
    static const bool value = std::is_same<_E_lhs, _E_rhs>::value;
};

template<typename ..._E>
using are_same_type_v = typename are_same_type<_E...>::value;
