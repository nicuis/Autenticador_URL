#ifndef DOMAIN_FILTER_HPP
#define DOMAIN_FILTER_HPP

#include "url_filter.hpp"

class domain_filter : public url_filter {
    
    private:
        std::unique_ptr<url_filter> next_filter;
    
    public:
        domain_filter(std::unique_ptr<url_filter> next_filter);
        void do_filter(std::string_view&& url) override;

    private:
        std::size_t find_domain_size(std::string_view& url);
        void validate_domain_and_port(std::string_view& domain);
        void validate_port_if_present_then_exclude(std::string_view& domain_with_port);
        bool is_valid_port(const std::string_view& port_str);
        bool has_any_dot(std::string_view& domain);
        bool starts_or_ends_with_dots(std::string_view& domain);
        bool has_double_dots(const std::string_view& domain);
        bool has_invalid_tld(std::string_view& domain);
        bool is_valid_domain_char(char c);
};

#endif