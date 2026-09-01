#include "token.h"
#include <any>
#include <ostream>
#include <string>

Token::Token(TokenType p_type, std::string p_lexeme, std::any p_literal)
    : type(p_type), lexeme(p_lexeme), literal(p_literal) {};

// print only the lexeme for now
std::ostream &operator<<(std::ostream &os, Token token) {
  return os << token.lexeme;
}
