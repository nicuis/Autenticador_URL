#ifndef URL_FILTERS_H
#define URL_FILTERS_H

#include <string>
#include <memory> // Smart pointers

class URLFilter {
    public:
        static bool validateURL(const std::shared_ptr<std::string>& url);
};
#endif