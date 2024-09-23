#include "url_filters.h"
#include <stdexcept>

namespace filters {

    bool URLFilter::validateURL(const std::shared_ptr<std::string>& url) {
        if (url->substr(0, 7) != "http://" && url->substr(0, 8) != "https://") {
            throw std::invalid_argument("URL deve começar com 'http://' ou 'https://'.");
        }

        std::string::size_type pos = url->find("://");
        if (pos == std::string::npos) {
            throw std::invalid_argument("Protocolo inválido na URL.");
        }

        std::string domain = url->substr(pos + 3);
        if (domain.empty()) {
            throw std::invalid_argument("URL sem domínio.");
        }

        if (domain.find('.') == std::string::npos || domain.back() == '.') {
            throw std::invalid_argument("Domínio inválido.");
        }

        return true;
    }

}
