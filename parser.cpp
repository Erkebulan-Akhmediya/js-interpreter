#include "parser.h"
#include "expr.h"
#include "token.h"
#include <concepts>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>

std::unique_ptr<Expr> Parser::parse() {
  try {
    return expression();
  } catch (ParserError &e) {
    auto expr = std::unique_ptr<Expr>();
    expr.reset();
    return expr;
  }
}

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

std::unique_ptr<Expr> Parser::primary() {
  if (match(TokenType::TRUE))
    return std::make_unique<Literal>(true);
  if (match(TokenType::FALSE))
    return std::make_unique<Literal>(false);
  if (match(TokenType::NULL_VALUE))
    return std::make_unique<Literal>();

  if (match(TokenType::NUM, TokenType::STR)) {
    std::variant<std::string_view, double> variant = previous().literal.value();
    if (auto val = std::get_if<std::string_view>(&variant))
      return std::make_unique<Literal>(std::string(*val));
    return std::make_unique<Literal>(*std::get_if<double>(&variant));
  }

  if (match(TokenType::LEFT_BRACET)) {
    auto expr = expression();
    if (!check(TokenType::RIGHT_BRACET))
      throw std::runtime_error(") expected");
    return std::make_unique<Grouping>(std::move(expr));
  }

  throw std::runtime_error("expression expected");
}

void Parser::sync() {
  advance();
  while (!isAtEnd()) {
    if (previous().type == TokenType::SEMICOL)
      return;
    switch (peek().type) {
    case TokenType::LET:
    case TokenType::IF:
    case TokenType::FOR:
    case TokenType::WHILE:
    case TokenType::FUNCTION:
    case TokenType::CONST:
    case TokenType::VAR:
      return;
    default:
      advance();
    }
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
