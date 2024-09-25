#ifndef PROTOCOL_FILTER_HPP
#define PROTOCOL_FILTER_HPP

#include "url_filter.hpp"

class protocol_filter : public url_filter {
    
    private:
        std::unique_ptr<url_filter> next_filter;
    
    public:
        protocol_filter(std::unique_ptr<url_filter> next_filter);
        void do_filter(std::string_view&& url) override;
    
    private:
        void checkForHttpThenRemove(std::string_view& url);
        void checkForSAndRemoveIfPresent(std::string_view& url);
        void checkForProtocolSeparatorThenRemove(std::string_view& url);
};

#endif