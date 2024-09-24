#include "url_validation_filter_chain.hpp"
#include "protocol_filter.hpp"
#include <memory>
#include <string>

url_validation_filter_chain::url_validation_filter_chain() {
    first_filter = std::make_unique<protocol_filter>();
}

void url_validation_filter_chain::validate(std::string_view& url) {
    first_filter->do_filter(std::move(url));
}