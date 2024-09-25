#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.hpp"
#include "../src/validators/url_validator.hpp"
#include "../src/exceptions/url_validation_exception.hpp"  

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
    REQUIRE_THROWS_AS(url_validator::validate("htp://exemplo.com"), url_validation_exception);    // Protocolo incorreto
    REQUIRE_THROWS_AS(url_validator::validate("httpss://exemplo.com"), url_validation_exception); // Protocolo incorreto
    
    // URLs com domínios inválidos
    REQUIRE_THROWS_AS(url_validator::validate("http://.com"), url_validation_exception);               // Domínio vazio
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo"), url_validation_exception);            // Falta o domínio de nível superior
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo..com"), url_validation_exception);       // Domínio com dois pontos
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com..com"), url_validation_exception);   // Domínio com dois pontos
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.c"), url_validation_exception);          // TLD muito curto
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com:"), url_validation_exception);       // Porta sem número
    REQUIRE_THROWS_AS(url_validator::validate("http:///exemplo.com"), url_validation_exception);       // Barras extras no protocolo
    REQUIRE_THROWS_AS(url_validator::validate("http:// exemplo.com"), url_validation_exception);       // Espaços na URL
    REQUIRE_THROWS_AS(url_validator::validate("ftp://exemplo.com"), url_validation_exception);         // Protocolo inválido
    
    // URLs com portas inválidas
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com:abc"), url_validation_exception);    // Porta com letras
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com:999999"), url_validation_exception); // Porta fora do intervalo permitido
    
    // URLs malformadas
    REQUIRE_THROWS_AS(url_validator::validate("http://"), url_validation_exception);
    REQUIRE_THROWS_AS(url_validator::validate("https://"), url_validation_exception);
    REQUIRE_THROWS_AS(url_validator::validate("://exemplo.com"), url_validation_exception);            // Protocolo ausente
    REQUIRE_THROWS_AS(url_validator::validate("http:exemplo.com"), url_validation_exception);          // Protocolo sem "//"
    
    // URLs com paths malformados
    REQUIRE_THROWS_AS(url_validator::validate("http:///exemplo.com//caminho"), url_validation_exception);       // Barras duplas no path
    REQUIRE_THROWS_AS(url_validator::validate("http:///exemplo.com/ caminho"), url_validation_exception);       // Espaço no path

    // URL com param malformado
    REQUIRE_THROWS_AS(url_validator::validate("https://exemplo.com/caminho/?query=valor&"), url_validation_exception);       // Param vazio
    REQUIRE_THROWS_AS(url_validator::validate("https://exemplo.com/caminho/?query=valor&&query=valor"), url_validation_exception);       // Param vazio

    // URLs com fragmentos incorretos
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com#"), url_validation_exception);       // Fragmento vazio
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com# "), url_validation_exception);      // Fragmento com espaço
}
