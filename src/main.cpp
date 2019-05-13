#include <iostream>

#include "ip/print.h"

/**
 * @brief Класс наследник DoxygenExampleClass.
 * Создан для тестирования генерации документации, и не несет никакой смыславой нагрузки по задания.
 *
 * @param  str - просто стринга
 * @author VKS <vks.skv@rambler.ru>
 */
class B : public Ip_NS::DoxygenExampleClass {
public:
    explicit B(const std::string &str) : DoxygenExampleClass(str), s_protected(str) {}

    const std::string &getSProtected() const {
        return s_protected;
    }

    void setSProtected(const std::string &sProtected) {
        s_protected = sProtected;
    }

protected:
    std::string s_protected;
};

int main() {
    new Ip_NS::DoxygenExampleClass();
    auto b = new B("test");

    std::cout << b->getSPublic() << " / " << b->getSProtected();

    return 0;
}