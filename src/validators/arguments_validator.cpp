#include "arguments_validator.h"
#include "../exceptions/exception_validator.h"
#include "../URL.h"
#include <stdexcept>

void ArgumentValidator::validateArgs(int argc, char* argv[]) const {
    
    std::string argument = argv[1];

    if (argc != 2) 
        throw exception_validator("Número insuficiente de argumentos.");

    if (argument.empty()) 
        throw exception_validator("O argumento fornecido está vazio.");
}