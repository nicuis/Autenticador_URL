#include "url_validation_filter_chain.hpp"
#include "domain_filter.hpp"
#include "fragment_filter.hpp"
#include "param_filter.hpp"
#include "path_filter.hpp"
#include "protocol_filter.hpp"

#include <memory>
#include <string>

url_validation_filter_chain::url_validation_filter_chain() {
    std::unique_ptr<url_filter> fragment_filter_part = std::make_unique<fragment_filter>();
    std::unique_ptr<url_filter> param_filter_part = std::make_unique<param_filter>(std::move(fragment_filter_part));
    std::unique_ptr<url_filter> path_filter_part = std::make_unique<path_filter>(std::move(param_filter_part));
    std::unique_ptr<url_filter> domain_filter_part = std::make_unique<domain_filter>(std::move(path_filter_part));
    first_filter = std::make_unique<protocol_filter>(std::move(domain_filter_part));
}

void url_validation_filter_chain::validate(std::string_view& url) {
    first_filter->do_filter(std::move(url));
}