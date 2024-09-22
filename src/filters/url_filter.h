#ifndef URL_FILTER_H
#define URL_FILTER_H

#include <string>
#include <memory> // Smart pointers

using namespace std;

namespace filters {

    class URLFilter {
    public:
        bool validateURL(const std::shared_ptr<string>& url);
    };

}

#endif