#include "url_validation_exception.hpp"

url_validation_exception::url_validation_exception(const std::string& message) : 
    std::runtime_error(message)
{}