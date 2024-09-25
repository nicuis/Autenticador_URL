#include "src/validators/arguments_validator.h"
#include "src/exceptions/exception_validator.h"
#include "src/io/show_texts.hpp"
#include <iostream>
#include <memory>

int main(int argc, char* argv[]){

    try {
        ArgumentValidator::validateArgs(argc, argv);
        showTexts::printText("URL válida!");
    
    } catch (const exception_validator& e) {
        showTexts::printError(e);
    }
    return 0;
}