#include "URL.h"

URL::URL(const std::string& urlString) : url(urlString) {}

std::string URL::getURL() const {
    return url;
}