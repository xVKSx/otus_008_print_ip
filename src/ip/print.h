/**
 * @brief преобразование в ip формат данные вида:
 *   - строка;
 *   - целочисленное значение;
 *   - контенер vector и list;
 *   - tuple (с учетом того, что все элементы одного типа)
 * @author VKS
 */

#pragma once

#include <type_traits>
#include <string>
#include <list>
#include <vector>
#include <tuple>
#include <sstream>

#include "../utility/type_traits.h"

namespace Ip_NS {

    ///print_tuple_item

    /**
     * @brief Формирование строки по-элементно
     * @tparam _idx
     * @tparam _max_idx
     * @tparam Args
     */
    template<size_t _idx, size_t _max_idx, typename ...Args>
    struct print_tuple_item {
        std::string operator()(const std::tuple<Args...> &tuple) {
            std::stringstream ss;
            if (_idx != 0) {
                ss << ".";
            }
            ss << std::get<_idx>(tuple);
            ss << print_tuple_item<_idx + 1, _max_idx, Args...>{}(tuple);

            return ss.str();
        }
    };

    /**
     * @tparam index_max
     * @tparam Args
     */
    template<size_t _max_idx, typename ...Args>
    struct print_tuple_item<_max_idx, _max_idx, Args...> {
        std::string operator()(const std::tuple<Args...> &) {
            return "";
        }
    };

    /// print_ip

    /**
     * @brief Приведение челочисленного значение к формату ipv4
     * @tparam _T челочисленного значение
     * @param ip
     * @return std::string
     * @todo необходимо разобраться, какое поведение при переполнении.
     * значние должно приводить к 123.45.67.89.101.112.131.41 ?
     */
    template<typename _T>
    typename std::enable_if_t<std::__is_integral_helper<_T>::value, std::string>
    print_ip(const _T &ip) {
        std::stringstream ss;

        ss << ((ip >> 24) & 0xff) << ".";
        ss << ((ip >> 16) & 0xff) << ".";
        ss << ((ip >> 8) & 0xff) << ".";
        ss << ((ip) & 0xff);

        return ss.str();
    }

    /**
     * @brief Приведение строки к формату ipv4
     * @tparam _T строка
     * @param ip
     * @return std::string фактически возврат значения
     * @todo необходимо понять, что реализация через type_traits имеет место быть
     */
    template<typename _T>
    typename std::enable_if_t<is_string<std::remove_const_t<_T>>::value, std::string>
    print_ip(const _T &ip) {
        return ip;
    }

    /**
     * @brief Приведение значений представленных в виде вектор или списка к формату ipv4
     * @tparam _T std::vector | std::list
     * @param ip
     * @return std::string
     */
    template<typename _T>
    typename std::enable_if_t<is_container<_T>::value, std::string>
    print_ip(const _T &ip) {
        std::stringstream ss;

        for (auto it = ip.begin(); it != ip.end();) {
            ss << *it;
            ss << (++it != ip.end() ? "." : "");
        }

        return ss.str();
    }

    /**
     * @brief Приведение значения tuple<...> к формату ipv4
     * @tparam _E
     * @param ip
     * @return std::string
     */
    template<typename ..._E>
    typename std::enable_if_t<are_same_type<_E...>::value, std::string>
    print_ip(const std::tuple<_E...> &ip) {
        static_assert(sizeof...(_E) == 4, "No IP");
        return print_tuple_item<0, sizeof...(_E), _E...>()(ip);
    }

}
