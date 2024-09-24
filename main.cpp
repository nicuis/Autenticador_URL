#include "src/validators/arguments_validator.h"
#include "src/exceptions/exception_validator.h"
#include "src/URL.h"

#include <iostream>
#include <memory>

int main(int argc, char* argv[]){

    std::shared_ptr<std::string> urlStr;

    try {

        ArgumentValidator::validateArgs(argc, argv, urlStr);
        std::cout << "URL válida: " << *urlStr << std::endl;
    
    } catch (const exception_validator& e) {
    
        std::cerr << "Erro de validação: " << e.what() << std::endl;
        return EXIT_FAILURE;
    
    } catch (const std::exception& e) {
    
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
        return EXIT_FAILURE;
    
    }

    return EXIT_SUCCESS;
}