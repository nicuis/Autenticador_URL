#include <stdexcept>
#include <string>
#include "url_validator.hpp"
#include "../filters/url_validation_filter_chain.hpp"

void url_validator::validate(std::string&& url) {
    url_validation_filter_chain validation_filter;
    std::string_view url_view(url);
    validation_filter.validate(url_view);
}