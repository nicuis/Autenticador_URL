#include "src/validators/arguments_validator.h"
#include "src/validators/url_validator.hpp"
#include "src/io/show_texts.hpp"
#include "src/exceptions/url_validation_exception.hpp"

int main(int argc, char* argv[]){

    try {
        ArgumentValidator::validateArgs(argc, argv);
        url_validator::validate(argv[1]);
        showTexts::printText("URL válida!");
    } catch (const url_validation_exception& e) {
        showTexts::printError(e);
    }
    return 0;
}