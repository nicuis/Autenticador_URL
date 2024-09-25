#include "param_filter.hpp"
#include "../exceptions/exception_validator.h"
#include <iostream>

param_filter::param_filter(std::unique_ptr<url_filter> next_filter) :
    next_filter(std::move(next_filter))
{}

void param_filter::do_filter(std::string_view&& url) {
    if (url[0] == '?') {
        url.remove_prefix(1);
        std::size_t param_end = find_param_size(url);
        std::string_view param = url.substr(0, param_end);
        validate_params(param);        
        url.remove_prefix(param_end);
    }
    if (!url.empty())
        next_filter->do_filter(std::move(url));
}

std::size_t param_filter::find_param_size(std::string_view& url) {
    std::size_t param_end = url.find_first_of('#');
    if (param_end == std::string_view::npos)
        param_end = url.size();
    return param_end;
}

void param_filter::validate_params(std::string_view& params) {
    check_that_has_no_empty_params(params);
    while (!params.empty()) {
        std::string_view current_param = retrieve_next_param(params);
        check_if_there_are_valid_key_and_value(current_param);
        remove_first_param(params);        
    }
}

void param_filter::check_that_has_no_empty_params(std::string_view& params) {
    if (!params.empty() && params.back() == '&')
        throw exception_validator("& não pode ser o último caractere.");
}

std::string_view param_filter::retrieve_next_param(std::string_view& params) {
    std::size_t ampersand_pos = params.find('&');
    std::string_view next_param = ampersand_pos == std::string_view::npos
        ? params
        : params.substr(0, ampersand_pos);
    if (next_param.empty())
            throw exception_validator("Parâmetro vazio encontrado antes do '&'.");
    return next_param;
}

std::size_t param_filter::find_equals_position(std::string_view& current_param) {
    std::size_t equal_pos = current_param.find('=');
    if (equal_pos == std::string_view::npos)
        throw exception_validator("Parâmetro sem valor (esperado 'chave=valor').");
    return equal_pos;
}

void param_filter::check_if_there_are_valid_key_and_value(std::string_view& current_param) {
    std::size_t equal_pos = find_equals_position(current_param);
    std::string_view key = current_param.substr(0, equal_pos);
    if (key.empty())
        throw exception_validator("Chave vazia em um parâmetro.");
    std::string_view value = current_param.substr(equal_pos + 1);
    if (value.empty())
        throw exception_validator("Valor vazio em um parâmetro.");
}

void param_filter::remove_first_param(std::string_view& params) {
    std::size_t ampersand_pos = params.find('&');
    params.remove_prefix(ampersand_pos == std::string_view::npos ? params.size() : ampersand_pos + 1);
}