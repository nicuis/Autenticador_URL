#ifndef SHOW_TEXTS_HPP
#define SHOW_TEXTS_HPP

#include <iostream>
#include <string>
#include "../exceptions/url_validation_exception.hpp"

class showTexts {

    private:
        showTexts() = delete;
        ~showTexts() = delete;

    public:
        static void printError(const url_validation_exception& e);
        static void printText(const std::string& text);
};
#endif