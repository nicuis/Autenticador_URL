#include "protocol_filter.hpp"
#include "../exceptions/exception_validator.h"

#include <iostream>

protocol_filter::protocol_filter() {

}

void protocol_filter::do_filter(std::string_view&& url) {
    checkForHttpThenRemove(url);
    checkForSAndRemoveIfPresent(url);
    checkForProtocolSeparatorThenRemove(url);
    std::cout << url << std::endl;
}

void protocol_filter::checkForHttpThenRemove(std::string_view& url) {
    if (url.size() < 4 || url.substr(0, 4).compare("http") != 0)
        throw exception_validator("Url invalida.");
    url.remove_prefix(4);
}

void protocol_filter::checkForSAndRemoveIfPresent(std::string_view& url) {
    if (url.size() >= 1 && url.substr(0, 1).compare("s") == 0)
        url.remove_prefix(1);
}

void protocol_filter::checkForProtocolSeparatorThenRemove(std::string_view& url) {
    if (url.size() < 3 && url.substr(0, 3).compare("://") != 0)
        throw exception_validator("Url invalida.");
    url.remove_prefix(3);
}
