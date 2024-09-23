#ifndef ARGUMENTS_VALIDATOR_H
#define ARGUMENTS_VALIDATOR_H

#include <memory>
#include <string>

namespace validator {

    class ArgumentValidator {
    public:
        static void validateArgs(int argc, char* argv[], std::shared_ptr<std::string>& urlStr);
    };

}
#endif