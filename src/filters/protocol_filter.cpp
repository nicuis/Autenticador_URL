#include "protocol_filter.hpp"
#include "../exceptions/url_validation_exception.hpp"

protocol_filter::protocol_filter(std::unique_ptr<url_filter> next_filter) :
    next_filter(std::move(next_filter))
{}

void protocol_filter::do_filter(std::string_view&& url) {
    checkForHttpThenRemove(url);
    checkForSAndRemoveIfPresent(url);
    checkForProtocolSeparatorThenRemove(url);
    next_filter->do_filter(std::move(url));
}

void protocol_filter::checkForHttpThenRemove(std::string_view& url) {
    if (url.size() < 4 || url.substr(0, 4).compare("http") != 0)
        throw url_validation_exception("Url invalida.");
    url.remove_prefix(4);
}

void protocol_filter::checkForSAndRemoveIfPresent(std::string_view& url) {
    if (url.size() >= 1 && url.substr(0, 1).compare("s") == 0)
        url.remove_prefix(1);
}

void protocol_filter::checkForProtocolSeparatorThenRemove(std::string_view& url) {
    if (url.size() < 3 || url.substr(0, 3).compare("://") != 0)
        throw url_validation_exception("Url invalida.");
    url.remove_prefix(3);
}
