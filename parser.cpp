#include "parser.h"
#include "expr.h"
#include "token.h"
#include <concepts>
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

std::unique_ptr<Expr> Parser::comparison() {
  std::unique_ptr<Expr> expr = term();
  while (match(TokenType::GREATER, TokenType::GREATER_EQ, TokenType::LESS,
               TokenType::LESS_EQ)) {
    Token op = previous();
    std::unique_ptr<Expr> right = term();
    expr = std::make_unique<Binary>(std::move(expr), std::move(right), op);
  }
  return expr;
}

std::unique_ptr<Expr> Parser::term() {
  std::unique_ptr<Expr> expr = factor();
  while (match(TokenType::PLUS, TokenType::MINUS)) {
    Token op = previous();
    std::unique_ptr<Expr> right = factor();
    expr = std::make_unique<Binary>(std::move(expr), std::move(right), op);
  }
  return expr;
}

std::unique_ptr<Expr> Parser::factor() {
  std::unique_ptr<Expr> expr = unary();
  while (match(TokenType::STAR, TokenType::SLASH)) {
    Token op = previous();
    std::unique_ptr<Expr> right = unary();
    expr = std::make_unique<Binary>(std::move(expr), std::move(right), op);
  }
  return expr;
}

std::unique_ptr<Expr> Parser::unary() {
  if (match(TokenType::EXCLAMATION, TokenType::MINUS)) {
    Token op = previous();
    std::unique_ptr<Expr> expr = unary();
    return std::make_unique<Unary>(op, std::move(expr));
  } else {
    std::unique_ptr<Expr> expr = primary();
    if (match(TokenType::INCREMENT, TokenType::DECREMENT)) {
      Token op = previous();
      return std::make_unique<Unary>(op, std::move(expr));
    }
    return expr;
  }
}

bool Parser::match(std::same_as<TokenType> auto... types) {
  for (auto type : {types...}) {
    if (check(type)) {
      advance();
      return true;
    }
  }
  return false;
}

bool Parser::check(TokenType type) {
  if (isAtEnd())
    return false;
  return peek().type == type;
}

Token Parser::advance() {
  if (!isAtEnd())
    ++current;
  return previous();
}

Token Parser::peek() { return tokens.at(current); }

Token Parser::previous() { return tokens.at(current - 1); }

bool Parser::isAtEnd() { return peek().type == TokenType::END; }
