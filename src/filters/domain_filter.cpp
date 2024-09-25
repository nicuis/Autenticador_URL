#include "domain_filter.hpp"
#include "../exceptions/exception_validator.h"
#include <stdexcept>

domain_filter::domain_filter(std::unique_ptr<url_filter> next_filter) :
    next_filter(std::move(next_filter))
{}

void domain_filter::do_filter(std::string_view&& url) {
    std::size_t domain_end = find_domain_size(url);
    std::string_view domain_with_port = url.substr(0, domain_end);
    validate_domain_and_port(domain_with_port);
    url.remove_prefix(domain_end);
    if (!url.empty())
        next_filter->do_filter(std::move(url));
}

std::size_t domain_filter::find_domain_size(std::string_view& url) {
    std::size_t domain_end = url.find_first_of("/?#");
    if (domain_end == std::string_view::npos)
        domain_end = url.size();
    return domain_end;
}

void domain_filter::validate_domain_and_port(std::string_view& domain) {
    validate_port_if_present_then_exclude(domain);
    if (domain.empty() || !has_any_dot(domain) || starts_or_ends_with_dots(domain)
            || has_double_dots(domain) || has_invalid_tld(domain))
        throw exception_validator("Domínio vazio.");
    for (char c : domain) {
        if (!is_valid_domain_char(c)) {
            throw exception_validator("Domínio contém caracteres inválidos.");
        }
    }
}

void domain_filter::validate_port_if_present_then_exclude(std::string_view& domain_with_port) {
    std::size_t port_pos = domain_with_port.find(':');
    if (port_pos != std::string_view::npos) {
        std::string_view port_str = domain_with_port.substr(port_pos + 1);
        if (port_str.empty() || !is_valid_port(port_str))
            throw exception_validator("Porta inválida.");
        domain_with_port.remove_suffix(domain_with_port.size() - port_pos);
    }
}

bool domain_filter::is_valid_port(const std::string_view& port_str) {
    if (port_str.size() > 4)
        return false;
    for (char c : port_str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool domain_filter::has_any_dot(std::string_view& domain) {
    return domain.find('.') != std::string_view::npos;
}

bool domain_filter::starts_or_ends_with_dots(std::string_view& domain) {
    return domain.front() == '.' || domain.back() == '.';
}

bool domain_filter::has_double_dots(const std::string_view& domain) {
    return domain.find("..") != std::string_view::npos;
}

bool domain_filter::has_invalid_tld(std::string_view& domain) {
    return domain[domain.size() - 1] == '.' || domain[domain.size() - 2] == '.';
}

bool domain_filter::is_valid_domain_char(char c) {
    return std::isalnum(c) || c == '-' || c == '.';
}