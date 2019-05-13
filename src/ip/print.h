#pragma once

#include <string>

namespace Ip_NS {
    class DoxygenExampleClass {
    public:
        explicit DoxygenExampleClass(const std::string &str = "") : s_public("public " + str) {}

        virtual ~DoxygenExampleClass() = default;

        const std::string &getSPublic() const;

    public:
        std::string s_public;
    };
}