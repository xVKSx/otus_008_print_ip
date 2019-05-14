#pragma once

#include <type_traits>
#include <string>
#include <list>
#include <vector>
#include <tuple>


namespace Ip_NS {

    template<typename T>
    struct is_string : std::false_type {
    };

    template<>
    struct is_string<std::string> : std::true_type {
    };

    template<typename T>
    struct is_container : std::false_type {
    };

    template<typename ... Args>
    struct is_container<std::vector<Args...>> : std::true_type {
    };

    template<typename ... Args>
    struct is_container<std::list<Args...>> : std::true_type {
    };

    template<typename ...E>
    struct is_same_type;

    template<typename E1, typename E2, typename ...E>
    struct is_same_type<E1, E2, E...> {
        static const bool value = std::is_same<E1, E2>::value && is_same_type<E2, E...>::value;
    };

    template<typename E1, typename E>
    struct is_same_type<E1, E> {
        static const bool value = std::is_same<E1, E>::value;
    };

    template<typename T>
    typename std::enable_if_t<std::is_integral<T>::value, std::string>
    print_ip(const T &) {
        return "int";
    }

    template<typename T>
    typename std::enable_if_t<is_string<std::remove_const_t<T>>::value, std::string>
    print_ip(const T &) {
        return "string";
    }

    template<typename T>
    typename std::enable_if_t<is_container<T>::value, std::string>
    print_ip(const T &) {
        return "vector or list";
    }

    template<typename ...E>
    typename std::enable_if_t<is_same_type<E...>::value, std::string> print_ip(const std::tuple<E...> &) {
        static_assert(sizeof...(E) == 4, "No IP");
        return "tuple";
    }

}