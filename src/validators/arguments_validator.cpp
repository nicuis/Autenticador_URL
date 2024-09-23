#include "arguments_validator.h"
#include "exception_validator.h"
#include "../filters/url_filters.h"
#include "../src/URL.h"
#include <stdexcept>

void ArgumentValidator::validateArgs(int argc, char* argv[], std::shared_ptr<std::string>& urlStr) {
    
    if (argc < 2) {
        throw exception_validator("Número insuficiente de argumentos.");
    }

    urlStr = std::make_shared<std::string>(argv[1]);

    URLFilter::validateURL(urlStr);
}