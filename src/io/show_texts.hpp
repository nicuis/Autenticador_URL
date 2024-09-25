#ifndef SHOW_TEXTS_HPP
#define SHOW_TEXTS_HPP

#include <iostream>
#include <string>
#include "../exceptions/exception_validator.h"

class showTexts {

    private:
        showTexts() = delete;
        ~showTexts() = delete;

    public:
        static void printError(const exception_validator& e);
        static void printText(const std::string& text);
};
#endif