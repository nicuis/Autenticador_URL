#include "path_filter.hpp"
#include "../exceptions/url_validation_exception.hpp"

path_filter::path_filter(std::unique_ptr<url_filter> next_filter) :
    next_filter(std::move(next_filter))
{}

void path_filter::do_filter(std::string_view&& url) {
    if (url[0] == '/') {
        std::size_t path_end = find_path_size(url);
        std::string_view path = url.substr(0, path_end);
        validate_path(path);
        url.remove_prefix(path_end);
    }
    if (!url.empty())
        next_filter->do_filter(std::move(url));
}

std::size_t path_filter::find_path_size(std::string_view& url) {
    std::size_t path_end = url.find_first_of("?#");
    if (path_end == std::string_view::npos) {
        path_end = url.size();
    }
    return path_end;
}

void path_filter::validate_path(std::string_view& path) {
    check_that_doesnt_have_double_bars(path);
    check_that_doesnt_have_invalid_chars(path);
}

void path_filter::check_that_doesnt_have_double_bars(std::string_view& path) {
    if (path.find("//") != std::string_view::npos)
        throw url_validation_exception("Caminho invalido.");
}

void path_filter::check_that_doesnt_have_invalid_chars(std::string_view& path) {
    if (path.find_first_of(" \"<>#%{}|\\^`") != std::string::npos)
        throw url_validation_exception("Caminho invalido.");
}