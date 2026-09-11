#include "parser.h"
#include "expr.h"
#include "token.h"
#include <memory>

std::unique_ptr<Expr> Parser::expression() { return equality(); }

std::unique_ptr<Expr> Parser::equality() {
  std::unique_ptr<Expr> expr = comparison();
  while (match(TokenType::EXCLAMATION_EQ, TokenType::DOUBLE_EQ)) {
    Token op = previous();
    std::unique_ptr<Expr> right = comparison();
    expr = std::make_unique<Binary>(std::move(expr), std::move(right), op);
  }
  return expr;
}
