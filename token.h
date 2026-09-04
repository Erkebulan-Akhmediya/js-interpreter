#ifndef TOKEN_H
#define TOKEN_H

#include <any>
#include <concepts>
#include <ostream>
#include <string>

enum class TokenType {
  // single char tokens
  EQ,
  SEMICOL,

  // multi char tokens

  // literals
  STR,
  NUM,

  // keywords
  LET,

  END
};

struct Token {
  TokenType type;
  std::string lexeme;
  std::any literal;

  Token(TokenType p_type, std::string p_lexeme, std::any p_literal);
};

std::ostream &operator<<(std::ostream &os, Token token);

#endif
