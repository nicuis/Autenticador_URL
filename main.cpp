#include "src/validators/arguments_validator.h"
#include "src/exceptions/url_validation_exception.hpp"
#include "src/io/show_texts.hpp"

int main(int argc, char* argv[]){

    try {
        ArgumentValidator::validateArgs(argc, argv);
        showTexts::printText("URL válida!");
    } catch (const url_validation_exception& e) {
        showTexts::printError(e);
    }
    return 0;
}