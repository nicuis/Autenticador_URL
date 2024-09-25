#ifndef URL_VALIDATION_EXCEPTION_HPP
#define URL_VALIDATION_EXCEPTION_HPP

#include <stdexcept>
#include <string>

class url_validation_exception : public std::runtime_error {
    
    public:
        explicit url_validation_exception(const std::string& message);
};

#endif