#ifndef URL_FILTERS_H
#define URL_FILTERS_H

#include <string>
#include <memory> // Smart pointers

using namespace std;

namespace filters {

    class URLFilter {
    public:
        static bool validateURL(const std::shared_ptr<string>& url);
    };

}

#endif