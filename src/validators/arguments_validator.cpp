#include "arguments_validator.h"
#include "../exceptions/url_validation_exception.hpp"
#include <stdexcept>

void ArgumentValidator::validateArgs(int argc, char* argv[]) {

    if (argc != 2) 
        throw url_validation_exception("Número insuficiente de argumentos.");

    std::string argument = argv[1];

    if (argument.empty()) 
        throw url_validation_exception("O argumento fornecido está vazio.");
}