#include "show_texts.hpp"

void showTexts::printError(const exception_validator& e) {
    std::cerr << "Erro de validação: " << e.what() << std::endl;
}

void showTexts::printText(const std::string& text) {
    std::cout << text << std::endl;
}