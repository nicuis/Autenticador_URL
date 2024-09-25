#ifndef PATH_FILTER_HPP
#define PATH_FILTER_HPP

#include "url_filter.hpp"

class path_filter : public url_filter {
    
    private:
        std::unique_ptr<url_filter> next_filter;
    
    public:
        path_filter(std::unique_ptr<url_filter> next_filter);
        void do_filter(std::string_view&& url) override;

    private:
        std::size_t find_path_size(std::string_view& url);
        void validate_path(std::string_view& path);
        void check_that_doesnt_have_double_bars(std::string_view& path);
        void check_that_doesnt_have_invalid_chars(std::string_view& path);
};

#endif