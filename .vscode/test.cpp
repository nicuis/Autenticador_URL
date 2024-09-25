#include <string>
#include "../src/filters/url_validation_filter_chain.hpp"

int main(int argc, char const *argv[])
{
    std::string_view a = "https://exemplo.com/caminho/?query=valor&";
    url_validation_filter_chain validator;
    validator.validate(a);
    return 0;
}
