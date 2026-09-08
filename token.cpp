#include "token.h"
#include <ostream>
#include <string>
#include <variant>

Token::Token(TokenType p_type, std::string p_lexeme,
             std::optional<std::variant<std::string, double>> p_literal)
    : type(p_type), lexeme(p_lexeme), literal(p_literal) {};

// print only the lexeme for now
std::ostream &operator<<(std::ostream &os, Token token) {
  os << "{ lexeme: " << token.lexeme;
  if (token.literal.has_value()) {
    os << ", literal: ";
    std::visit([&os](auto &&literal) { os << literal; }, token.literal.value());
  }
  os << "}";
  return os;
}
