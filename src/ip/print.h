#pragma once

#include <type_traits>
#include <string>
#include <list>
#include <vector>
#include <tuple>
#include <sstream>


namespace Ip_NS {

    template<typename _T>
    struct is_string : std::false_type {
    };

    template<>
    struct is_string<std::string> : std::true_type {
    };

    template<typename _T>
    struct is_container : std::false_type {
    };

    template<typename ... Args>
    struct is_container<std::vector<Args...>> : std::true_type {
    };

    template<typename ... Args>
    struct is_container<std::list<Args...>> : std::true_type {
    };

    template<typename ...E>
    struct are_same_type;

    template<typename E1, typename E2, typename ...E>
    struct are_same_type<E1, E2, E...> {
        static const bool value = std::is_same<E1, E2>::value && are_same_type<E2, E...>::value;
    };

    template<typename E1, typename E>
    struct are_same_type<E1, E> {
        static const bool value = std::is_same<E1, E>::value;
    };

    template<typename ...E>
    using are_same_type_v = typename are_same_type<E...>::value;

    template<size_t index, size_t index_max, typename... Args>
    struct print_tuple_item {
        std::string operator()(const std::tuple<Args...> &tuple) {
            std::stringstream ss;
            if (index != 0) {
                ss << ".";
            }
            ss << std::get<index>(tuple);
            ss << print_tuple_item<index + 1, index_max, Args...>{}(tuple);

            return ss.str();
        }
    };

    template<size_t index_max, typename... Args>
    struct print_tuple_item<index_max, index_max, Args...> {
        std::string operator()(const std::tuple<Args...> &) {
            return "";
        }
    };

    template<typename T>
    typename std::enable_if_t<std::__is_integral_helper<T>::value, std::string>
    print_ip(const T &ip) {
        std::stringstream ss;

        ss << ((ip >> 24) & 0xff) << ".";
        ss << ((ip >> 16) & 0xff) << ".";
        ss << ((ip >> 8) & 0xff) << ".";
        ss << ((ip) & 0xff);

        return ss.str();
    }

    template<typename T>
    typename std::enable_if_t<is_string<std::remove_const_t<T>>::value, std::string>
    print_ip(const T &ip) {
        return ip;
    }

    template<typename T>
    typename std::enable_if_t<is_container<T>::value, std::string>
    print_ip(const T &ip) {
        std::stringstream ss;

        for (auto it = ip.begin(); it != ip.end();) {
            ss << *it;
            ss << (++it != ip.end() ? "." : "");
        }

        return ss.str();
    }

    template<typename ...E>
    typename std::enable_if_t<are_same_type<E...>::value, std::string>
    print_ip(const std::tuple<E...> &ip) {
        static_assert(sizeof...(E) == 4, "No IP");
        return print_tuple_item<0, sizeof...(E), E...>()(ip);
    }

}
