#include "url_filters.h"
#include "../validators/exception_validator.h"
#include <stdexcept>

bool URLFilter::validateURL(const std::shared_ptr<std::string>& url) {

    if (url->substr(0, 7) != "http://" && url->substr(0, 8) != "https://") {
        throw exception_validator("URL deve começar com 'http://' ou 'https://'.");
    }
    std::string::size_type pos = url->find("://");
    if (pos == std::string::npos) {
        throw exception_validator("Protocolo inválido na URL.");
    }
    std::string domain = url->substr(pos + 3);
    if (domain.empty()) {
        throw exception_validator("URL sem domínio.");
    }
    if (domain.find('.') == std::string::npos || domain.back() == '.') {
        throw exception_validator("Domínio inválido.");
    }
    return true;
}