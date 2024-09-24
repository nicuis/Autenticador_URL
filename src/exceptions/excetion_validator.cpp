#include "exception_validator.h"

exception_validator::exception_validator(const std::string& message) : 
std::runtime_error(message){}
