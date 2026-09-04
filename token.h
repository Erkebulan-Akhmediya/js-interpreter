#ifndef TOKEN_H
#define TOKEN_H

#include <any>
#include <concepts>
#include <ostream>
#include <string>

enum class TokenType {
  // single char tokens
  EQ,
  GREATER,
  LESS,
  EXCLAMATION,
  SEMICOL,
  MINUS,
  PLUS,
  SLASH,
  PERCENT,
  STAR,
  COMMA,
  SINGLE_QUOTE,
  DOUBLE_QUOTE,
  LEFT_BRACET,
  RIGHT_BRACET,
  LEFT_CURLY_BRACET,
  RIGHT_CURLY_BRACET,
  AND,
  OR,

  // multi char tokens
  DOUBLE_EQ,
  GREATER_EQ,
  LESS_EQ,
  EXCLAMATION_EQ,
  INCREMENT,
  DECREMENT,
  PLUS_EQ,
  MINUS_EQ,
  STAR_EQ,
  SLASH_EQ,
  PERCENT_EQ,

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
