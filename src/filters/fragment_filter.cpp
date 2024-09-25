#include "fragment_filter.hpp"
#include "../exceptions/url_validation_exception.hpp"

void fragment_filter::do_filter(std::string_view&& url) {
    if (url[0] != '#')
        throw url_validation_exception("Fragmento invalido.");
    validate_fragment(url);
}

void fragment_filter::validate_fragment(std::string_view& fragment) {
    if (fragment.size() == 1 && fragment[0] == '#')
        throw url_validation_exception("Fragmento invalido.");
    fragment.remove_prefix(1);
    check_that_doesnt_have_double_bars(fragment);
    check_that_doesnt_have_invalid_chars(fragment);
}

void fragment_filter::check_that_doesnt_have_double_bars(std::string_view& fragment) {
    if (fragment.find("//") != std::string_view::npos)
        throw url_validation_exception("Fragmento invalido.");
}

void fragment_filter::check_that_doesnt_have_invalid_chars(std::string_view& fragment) {
    std::string invalid_chars = " \"<>\\^`{|}";
    if (fragment.find_first_of(invalid_chars) != std::string_view::npos)
        throw url_validation_exception("Fragmento invalido.");
}