#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>

#include "ip/print.h"

/**
 * @brief Класс наследник DoxygenExampleClass.
 * Создан для тестирования генерации документации, и не несет никакой смыславой нагрузки по задания.
 *
 * @param  str - просто стринга
 * @author VKS <vks.skv@rambler.ru>
 */
//class B : public Ip_NS::DoxygenExampleClass {
//public:
//    explicit B(const std::string &str) : DoxygenExampleClass(str), s_protected(str) {}
//
//    const std::string &getSProtected() const {
//        return s_protected;
//    }
//
//    void setSProtected(const std::string &sProtected) {
//        s_protected = sProtected;
//    }
//
//protected:
//    std::string s_protected;
//};

int main() {

    std::cout << Ip_NS::print_ip(char(-1)) << std::endl;

    std::cout << Ip_NS::print_ip(short(0)) << std::endl;

    std::cout << Ip_NS::print_ip(int(2130706433)) << std::endl;

    std::cout << Ip_NS::print_ip(long(8875824491850138409)) << std::endl;

    std::cout << Ip_NS::print_ip(std::string("127.0.0.1")) << std::endl;

    std::cout << Ip_NS::print_ip(std::vector<std::string>{"192", "168", "0", "100"}) << std::endl;

    std::cout << Ip_NS::print_ip(std::list<int>{192, 168, 0, 200}) << std::endl;

    std::cout << Ip_NS::print_ip(std::make_tuple("192", "168", "0", "255")) << std::endl;

    std::cout << Ip_NS::print_ip(std::make_tuple(192, 168, 0, 254)) << std::endl;

    return 0;

}