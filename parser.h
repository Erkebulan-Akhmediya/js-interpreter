#ifndef PARSER
#define PARSER

#include "expr.h"
#include "token.h"
#include <concepts>
#include <memory>
#include <vector>

class Parser {
private:
  const std::vector<Token> tokens;
  int current = 0;

  std::unique_ptr<Expr> expression();
  std::unique_ptr<Expr> equality();
  std::unique_ptr<Expr> comparison();
  std::unique_ptr<Expr> term();

  bool match(std::same_as<TokenType> auto... types);
  bool check(TokenType type);

  Token advance();
  Token peek();
  Token previous();

  bool isAtEnd();

public:
  Parser(std::vector<Token> t) : tokens(t) {}
};

#endif
