#ifndef PARSER
#define PARSER

#include "expr.h"
#include "token.h"
#include <concepts>
#include <memory>
#include <stdexcept>
#include <vector>


class ParserError : std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

class Parser {
private:
  const std::vector<Token> tokens;
  int current = 0;

  std::unique_ptr<Expr> expression();
  std::unique_ptr<Expr> equality();
  std::unique_ptr<Expr> comparison();
  std::unique_ptr<Expr> term();
  std::unique_ptr<Expr> factor();
  std::unique_ptr<Expr> unary();
  std::unique_ptr<Expr> primary();

  bool match(std::same_as<TokenType> auto... types);
  bool check(TokenType type);

  Token advance();
  Token peek();
  Token previous();
  void sync();

  bool isAtEnd();

public:
  Parser(std::vector<Token> t) : tokens(t) {};

  std::unique_ptr<Expr> parse();
};

#endif
