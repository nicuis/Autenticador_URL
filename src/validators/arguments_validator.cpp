#include "arguments_validator.h"
#include "../filters/url_filters.h"
#include "../filters/URL.h"
#include <stdexcept>

namespace validator {

    void ArgumentValidator::validateArgs(int argc, char* argv[], std::shared_ptr<std::string>& urlStr) {
        if (argc < 2) {
            throw std::invalid_argument("Número insuficiente de argumentos.");
        }

        urlStr = std::make_shared<std::string>(argv[1]);

        filters::URLFilter::validateURL(urlStr);
    }
}