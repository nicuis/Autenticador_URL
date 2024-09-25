#ifndef FRAGMENT_FILTER_HPP
#define FRAGMENT_FILTER_HPP

#include "url_filter.hpp"

class fragment_filter : public url_filter {
    
    public:
        fragment_filter() = default;
        void do_filter(std::string_view&& url) override;
    
    private:
        void validate_fragment(std::string_view& fragment);
        void check_that_doesnt_have_double_bars(std::string_view& fragment);
        void check_that_doesnt_have_invalid_chars(std::string_view& fragment);
};

#endif