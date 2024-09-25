#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.hpp"
#include "../src/validators/url_validator.hpp"
#include "../src/exceptions/exception_validator.h"  

TEST_CASE("Valid URLs", "[url]") {

    // URLs válidas
    REQUIRE_NOTHROW(url_validator::validate("http://exemplo.com"));
    REQUIRE_NOTHROW(url_validator::validate("https://exemplo.com"));
    REQUIRE_NOTHROW(url_validator::validate("http://sub.exemplo.com"));
    REQUIRE_NOTHROW(url_validator::validate("https://exemplo.com.br"));
    REQUIRE_NOTHROW(url_validator::validate("http://exemplo.com/caminho"));
    REQUIRE_NOTHROW(url_validator::validate("https://exemplo.com/caminho/para/recurso"));
    REQUIRE_NOTHROW(url_validator::validate("http://exemplo.com/caminho/para/recurso?query=valor"));
    REQUIRE_NOTHROW(url_validator::validate("https://exemplo.com/caminho?query=valor&outro=valor2"));
    REQUIRE_NOTHROW(url_validator::validate("http://exemplo.com:8080"));
    REQUIRE_NOTHROW(url_validator::validate("http://sub.dominio.com:8080/caminho?query=valor"));

    // URLs com parâmetros complexos e fragmentos
    REQUIRE_NOTHROW(url_validator::validate("https://exemplo.com/caminho?query=valor&chave=valor#sessao1"));
    REQUIRE_NOTHROW(url_validator::validate("https://exemplo.com/caminho?query=complexo%20query&outro=valor#header"));
    
    // URLs com subdomínios e caminhos
    REQUIRE_NOTHROW(url_validator::validate("http://sub.sub.exemplo.com"));
    REQUIRE_NOTHROW(url_validator::validate("https://sub.sub.exemplo.com:8080"));
    REQUIRE_NOTHROW(url_validator::validate("http://exemplo.com/"));
    REQUIRE_NOTHROW(url_validator::validate("https://exemplo.com/#fragmento"));
    REQUIRE_NOTHROW(url_validator::validate("http://exemplo.com/caminho/"));
    REQUIRE_NOTHROW(url_validator::validate("https://exemplo.com/caminho/?query=valor"));
    
    // URLs com diferentes formatos de porta
    REQUIRE_NOTHROW(url_validator::validate("http://exemplo.com:80/caminho"));
    REQUIRE_NOTHROW(url_validator::validate("http://exemplo.com:443/caminho"));
}

TEST_CASE("Invalid URLs", "[url]") {

    // URLs com erros de protocolo
    REQUIRE_THROWS_AS(url_validator::validate("htp://exemplo.com"), exception_validator);    // Protocolo incorreto
    REQUIRE_THROWS_AS(url_validator::validate("httpss://exemplo.com"), exception_validator); // Protocolo incorreto
    
    // URLs com domínios inválidos
    REQUIRE_THROWS_AS(url_validator::validate("http://.com"), exception_validator);               // Domínio vazio
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo"), exception_validator);            // Falta o domínio de nível superior
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo..com"), exception_validator);       // Domínio com dois pontos
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com..com"), exception_validator);   // Domínio com dois pontos
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.c"), exception_validator);          // TLD muito curto
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com:"), exception_validator);       // Porta sem número
    REQUIRE_THROWS_AS(url_validator::validate("http:///exemplo.com"), exception_validator);       // Barras extras no protocolo
    REQUIRE_THROWS_AS(url_validator::validate("http:// exemplo.com"), exception_validator);       // Espaços na URL
    REQUIRE_THROWS_AS(url_validator::validate("ftp://exemplo.com"), exception_validator);         // Protocolo inválido
    
    // URLs com portas inválidas
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com:abc"), exception_validator);    // Porta com letras
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com:999999"), exception_validator); // Porta fora do intervalo permitido
    
    // URLs malformadas
    REQUIRE_THROWS_AS(url_validator::validate("http://"), exception_validator);
    REQUIRE_THROWS_AS(url_validator::validate("https://"), exception_validator);
    REQUIRE_THROWS_AS(url_validator::validate("://exemplo.com"), exception_validator);            // Protocolo ausente
    REQUIRE_THROWS_AS(url_validator::validate("http:exemplo.com"), exception_validator);          // Protocolo sem "//"
    
    // URLs com paths malformados
    REQUIRE_THROWS_AS(url_validator::validate("http:///exemplo.com//caminho"), exception_validator);       // Barras duplas no path
    REQUIRE_THROWS_AS(url_validator::validate("http:///exemplo.com/ caminho"), exception_validator);       // Espaço no path

    // URL com param malformado
    REQUIRE_THROWS_AS(url_validator::validate("https://exemplo.com/caminho/?query=valor&"), exception_validator);       // Param vazio
    REQUIRE_THROWS_AS(url_validator::validate("https://exemplo.com/caminho/?query=valor&&query=valor"), exception_validator);       // Param vazio

    // URLs com fragmentos incorretos
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com#"), exception_validator);       // Fragmento vazio
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com# "), exception_validator);      // Fragmento com espaço
}
