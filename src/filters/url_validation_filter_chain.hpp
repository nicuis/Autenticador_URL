#ifndef URL_VALIDATION_FILTER_CHAIN
#define URL_VALIDATION_FILTER_CHAIN

#include <memory>
#include <string>
#include "url_filter.hpp"

class url_validation_filter_chain {

    private:
        std::unique_ptr<url_filter> first_filter;

    public:
        url_validation_filter_chain();
        ~url_validation_filter_chain() = default;
        void validate(std::string_view& url);
};

#endif