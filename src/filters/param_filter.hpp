#ifndef PARAM_FILTER_HPP
#define PARAM_FILTER_HPP

#include "url_filter.hpp"

class param_filter : public url_filter {
    
    private:
        std::unique_ptr<url_filter> next_filter;
    
    public:
        param_filter(std::unique_ptr<url_filter> next_filter);
        void do_filter(std::string_view&& url) override;

    private:
        void validate_params(std::string_view& param);
        std::size_t find_param_size(std::string_view& url);
        void check_that_has_no_empty_params(std::string_view& params);
        std::string_view retrieve_next_param(std::string_view& params);
        std::size_t find_equals_position(std::string_view& current_param);
        void check_if_there_are_valid_key_and_value(std::string_view& current_param);
        void remove_first_param(std::string_view& params);
};

#endif