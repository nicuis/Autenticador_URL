#ifndef URL_H
#define URL_H

#include <string>
using namespace std;

class URL {
    private:
        string url;
    public:
        URL(const string& urlString);
        string getURL() const;  // Retorna a URL
};
#endif