#define CATCH_CONFIG_MAIN
#include <string>
#include "catch.hpp"
#include "../src/validators/url_validator.hpp"  

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
    
    // URLs com IPs válidos (IPv4)
    REQUIRE_NOTHROW(url_validator::validate("http://192.168.0.1"));
    REQUIRE_NOTHROW(url_validator::validate("http://192.168.0.1:8080"));
    REQUIRE_NOTHROW(url_validator::validate("https://127.0.0.1"));
    REQUIRE_NOTHROW(url_validator::validate("https://127.0.0.1:8080/caminho?query=valor"));
}

TEST_CASE("Invalid URLs", "[url]") {

    // URLs com erros de protocolo
    REQUIRE_THROWS_AS(url_validator::validate("htp://exemplo.com"), std::invalid_argument);    // Protocolo incorreto
    REQUIRE_THROWS_AS(url_validator::validate("httpss://exemplo.com"), std::invalid_argument); // Protocolo incorreto
    
    // URLs com domínios inválidos
    REQUIRE_THROWS_AS(url_validator::validate("http://.com"), std::invalid_argument);               // Domínio vazio
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo"), std::invalid_argument);            // Falta o domínio de nível superior
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo..com"), std::invalid_argument);       // Domínio com dois pontos
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com..com"), std::invalid_argument);   // Domínio com dois pontos
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.c"), std::invalid_argument);          // TLD muito curto
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com:"), std::invalid_argument);       // Porta sem número
    REQUIRE_THROWS_AS(url_validator::validate("http:///exemplo.com"), std::invalid_argument);       // Barras extras no protocolo
    REQUIRE_THROWS_AS(url_validator::validate("http:// exemplo.com"), std::invalid_argument);       // Espaços na URL
    REQUIRE_THROWS_AS(url_validator::validate("ftp://exemplo.com"), std::invalid_argument);         // Protocolo inválido
    
    // URLs com portas inválidas
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com:abc"), std::invalid_argument);    // Porta com letras
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com:999999"), std::invalid_argument); // Porta fora do intervalo permitido
    
    // URLs com IPs inválidos (IPv4)
    REQUIRE_THROWS_AS(url_validator::validate("http://999.999.999.999"), std::invalid_argument);    // Endereço IP inválido
    REQUIRE_THROWS_AS(url_validator::validate("http://256.256.256.256"), std::invalid_argument);    // Endereço IP inválido
    REQUIRE_THROWS_AS(url_validator::validate("http://192.168.0"), std::invalid_argument);          // Endereço IP incompleto
    REQUIRE_THROWS_AS(url_validator::validate("http://192.168.0.1.1"), std::invalid_argument);      // Endereço IP com muitos octetos
    
    // URLs malformadas
    REQUIRE_THROWS_AS(url_validator::validate("http://"), std::invalid_argument);
    REQUIRE_THROWS_AS(url_validator::validate("https://"), std::invalid_argument);
    REQUIRE_THROWS_AS(url_validator::validate("://exemplo.com"), std::invalid_argument);            // Protocolo ausente
    REQUIRE_THROWS_AS(url_validator::validate("http:exemplo.com"), std::invalid_argument);          // Protocolo sem "//"
    
    // URLs com fragmentos incorretos
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com#"), std::invalid_argument);       // Fragmento vazio
    REQUIRE_THROWS_AS(url_validator::validate("http://exemplo.com# "), std::invalid_argument);      // Fragmento com espaço
}
