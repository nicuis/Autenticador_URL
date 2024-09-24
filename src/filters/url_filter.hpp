#ifndef URL_FILTER_HPP
#define URL_FILTER_HPP

#include <memory>
#include <string>

class url_filter {

    public:
        virtual ~url_filter() = default;
        virtual void do_filter(std::string_view&& url) = 0;
};

#endif