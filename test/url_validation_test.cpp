#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>

// TODO: Método a ser removido pois é outro o objeto de validação a ser testado 
bool isValidUrl(const std::string& url) {
    return false;
}

TEST_CASE("Valid URLs", "[url]") {

    // URLs válidas
    REQUIRE(isValidUrl("http://exemplo.com"));
    REQUIRE(isValidUrl("https://exemplo.com"));
    REQUIRE(isValidUrl("http://sub.exemplo.com"));
    REQUIRE(isValidUrl("https://exemplo.com.br"));
    REQUIRE(isValidUrl("http://exemplo.com/caminho"));
    REQUIRE(isValidUrl("https://exemplo.com/caminho/para/recurso"));
    REQUIRE(isValidUrl("http://exemplo.com/caminho/para/recurso?query=valor"));
    REQUIRE(isValidUrl("https://exemplo.com/caminho?query=valor&outro=valor2"));
    REQUIRE(isValidUrl("http://exemplo.com:8080"));
    REQUIRE(isValidUrl("http://sub.dominio.com:8080/caminho?query=valor"));

    // URLs com parâmetros complexos e fragmentos
    REQUIRE(isValidUrl("https://exemplo.com/caminho?query=valor&chave=valor#sessao1"));
    REQUIRE(isValidUrl("https://exemplo.com/caminho?query=complexo%20query&outro=valor#header"));
    
    // URLs com subdomínios e caminhos
    REQUIRE(isValidUrl("http://sub.sub.exemplo.com"));
    REQUIRE(isValidUrl("https://sub.sub.exemplo.com:8080"));
    REQUIRE(isValidUrl("http://exemplo.com/"));
    REQUIRE(isValidUrl("https://exemplo.com/#fragmento"));
    REQUIRE(isValidUrl("http://exemplo.com/caminho/"));
    REQUIRE(isValidUrl("https://exemplo.com/caminho/?query=valor"));
    
    // URLs com diferentes formatos de porta
    REQUIRE(isValidUrl("http://exemplo.com:80/caminho"));
    REQUIRE(isValidUrl("http://exemplo.com:443/caminho"));
    
    // URLs com IPs válidos (IPv4)
    REQUIRE(isValidUrl("http://192.168.0.1"));
    REQUIRE(isValidUrl("http://192.168.0.1:8080"));
    REQUIRE(isValidUrl("https://127.0.0.1"));
    REQUIRE(isValidUrl("https://127.0.0.1:8080/caminho?query=valor"));
}

TEST_CASE("Invalid URLs", "[url]") {

    // URLs com erros de protocolo
    REQUIRE_FALSE(isValidUrl("htp://exemplo.com"));    // Protocolo incorreto
    REQUIRE_FALSE(isValidUrl("httpss://exemplo.com")); // Protocolo incorreto
    
    // URLs com domínios inválidos
    REQUIRE_FALSE(isValidUrl("http://.com"));               // Domínio vazio
    REQUIRE_FALSE(isValidUrl("http://exemplo"));            // Falta o domínio de nível superior
    REQUIRE_FALSE(isValidUrl("http://exemplo..com"));       // Domínio com dois pontos
    REQUIRE_FALSE(isValidUrl("http://exemplo.com..com"));   // Domínio com dois pontos
    REQUIRE_FALSE(isValidUrl("http://exemplo.c"));          // TLD muito curto
    REQUIRE_FALSE(isValidUrl("http://exemplo.com:"));       // Porta sem número
    REQUIRE_FALSE(isValidUrl("http:///exemplo.com"));       // Barras extras no protocolo
    REQUIRE_FALSE(isValidUrl("http:// exemplo.com"));       // Espaços na URL
    REQUIRE_FALSE(isValidUrl("ftp://exemplo.com"));         // Protocolo inválido
    
    // URLs com portas inválidas
    REQUIRE_FALSE(isValidUrl("http://exemplo.com:abc"));    // Porta com letras
    REQUIRE_FALSE(isValidUrl("http://exemplo.com:999999")); // Porta fora do intervalo permitido
    
    // URLs com IPs inválidos (IPv4)
    REQUIRE_FALSE(isValidUrl("http://999.999.999.999"));    // Endereço IP inválido
    REQUIRE_FALSE(isValidUrl("http://256.256.256.256"));    // Endereço IP inválido
    REQUIRE_FALSE(isValidUrl("http://192.168.0"));          // Endereço IP incompleto
    REQUIRE_FALSE(isValidUrl("http://192.168.0.1.1"));      // Endereço IP com muitos octetos
    
    // URLs malformadas
    REQUIRE_FALSE(isValidUrl("http://"));
    REQUIRE_FALSE(isValidUrl("https://"));
    REQUIRE_FALSE(isValidUrl("://exemplo.com"));            // Protocolo ausente
    REQUIRE_FALSE(isValidUrl("http:exemplo.com"));          // Protocolo sem "//"
    
    // URLs com fragmentos incorretos
    REQUIRE_FALSE(isValidUrl("http://exemplo.com#"));       // Fragmento vazio
    REQUIRE_FALSE(isValidUrl("http://exemplo.com# "));      // Fragmento com espaço
}
