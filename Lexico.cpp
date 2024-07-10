#include <iostream>
#include <string>
#include <vector>
#include <regex>

// Definimos los tipos de tokens
enum TokenType {
    SELECT,
    FROM,
    WHERE,
    ORDER_BY,
    ASC,
    DESC,
    AND,
    OR,
    EQUALS,
    NOT_EQUALS,
    LESS_THAN,
    GREATER_THAN,
    LESS_EQUALS,
    GREATER_EQUALS,
    IDENTIFIER,
    LITERAL,
    ASTERISK,
    COMMA,
    DOT,
    OPEN_PAREN,
    CLOSE_PAREN,
    UNKNOWN
};

// Mapeamos los nombres de los tokens
std::string tokenNames[] = {
    "SELECT",
    "FROM",
    "WHERE",
    "ORDER BY",
    "ASC",
    "DESC",
    "AND",
    "OR",
    "=",
    "!=",
    "<",
    ">",
    "<=",
    ">=",
    "IDENTIFIER",
    "LITERAL",
    "*",
    ",",
    ".",
    "(",
    ")",
    "UNKNOWN"
};

// Estructura para almacenar un token y su tipo
struct Token {
    std::string value;
    TokenType type;
};

// Función que identifica el tipo de token
TokenType identifyToken(const std::string& word) {
    static std::regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");
    static std::regex literalRegex("[0-9]+|\\.|\\\"\\.");
    
    if (word == "SELECT") return SELECT;
    if (word == "FROM") return FROM;
    if (word == "WHERE") return WHERE;
    if (word == "ORDER") return ORDER_BY;
    if (word == "BY") return ORDER_BY;
    if (word == "ASC") return ASC;
    if (word == "DESC") return DESC;
    if (word == "AND") return AND;
    if (word == "OR") return OR;
    if (word == "=") return EQUALS;
    if (word == "!=") return NOT_EQUALS;
    if (word == "<") return LESS_THAN;
    if (word == ">") return GREATER_THAN;
    if (word == "<=") return LESS_EQUALS;
    if (word == ">=") return GREATER_EQUALS;
    if (word == "*") return ASTERISK;
    if (word == ",") return COMMA;
    if (word == ".") return DOT;
    if (word == "(") return OPEN_PAREN;
    if (word == ")") return CLOSE_PAREN;
    if (std::regex_match(word, identifierRegex)) return IDENTIFIER;
    if (std::regex_match(word, literalRegex)) return LITERAL;
    
    return UNKNOWN;
}

// Función que tokeniza la sentencia SQL
std::vector<Token> tokenize(const std::string& query) {
    std::vector<Token> tokens;
    std::regex wordRegex("([a-zA-Z_][a-zA-Z0-9_]*|[0-9]+|\\.|\\\"\\.|\\*|,|\\.|\\(|\\)|!=|<=|>=|<|>|=|\\s+)");
    auto words_begin = std::sregex_iterator(query.begin(), query.end(), wordRegex);
    auto words_end = std::sregex_iterator();
    
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string word = match.str();
        TokenType type = identifyToken(word);
        if (type != UNKNOWN) {
            tokens.push_back({ word, type });
        }
    }
    
    return tokens;
}


