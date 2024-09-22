#include "url_filter.h"
#include "URL.h"
#include <stdexcept>

using namespace std;

namespace filters {
    
     bool URLFilter::validateURL(const shared_ptr<URL>& url) {
        string urlStr = url->getURL(); 
        if (urlStr.substr(0, 7) != "http://" && urlStr.substr(0, 8) != "https://") {
            throw invalid_argument("URL deve começar com 'http://' ou 'https://'.");
        }

        string::size_type pos = urlStr.find("://");
        if (pos == string::npos) {
            throw invalid_argument("Protocolo inválido na URL.");
        }

        string domain = urlStr.substr(pos + 3);
        if (domain.empty()) {
            throw invalid_argument("URL sem domínio.");
        }

        if (domain.find('.') == string::npos || domain.back() == '.') {
            throw invalid_argument("Domínio inválido.");
        }

        return true;
    }

}    