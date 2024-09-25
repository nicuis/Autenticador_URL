#include "fragment_filter.hpp"
#include "../exceptions/exception_validator.h"
#include <iostream>
#include <stdexcept>
#include <cctype>

void fragment_filter::do_filter(std::string_view&& url) {
    if (url[0] != '#')
        throw exception_validator("Fragmento deve começar com '#'.");
    validate_fragment(url);
}

void fragment_filter::validate_fragment(std::string_view& fragment) {
    if (fragment.size() == 1 && fragment[0] == '#')
        throw exception_validator("O fragmento da URL está vazio.");
    fragment.remove_prefix(1);
    check_that_doesnt_have_double_bars(fragment);
    check_that_doesnt_have_invalid_chars(fragment);
}

void fragment_filter::check_that_doesnt_have_double_bars(std::string_view& fragment) {
    if (fragment.find("//") != std::string_view::npos)
        throw exception_validator("O fragmento contém barras duplas.");
}

void fragment_filter::check_that_doesnt_have_invalid_chars(std::string_view& fragment) {
    std::string invalid_chars = " \"<>\\^`{|}";
    if (fragment.find_first_of(invalid_chars) != std::string_view::npos)
        throw exception_validator("O fragmento contém caracteres inválidos.");
}