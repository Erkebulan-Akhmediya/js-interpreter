#ifndef EXPR
#define EXPR

#include "token.h"
#include <any>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>

struct Literal;
struct Grouping;
struct Unary;
struct Binary;
struct Ternary;

struct Visitor {
  virtual std::any visitLiteralExpr(const Literal *expr) const = 0;
  virtual std::any visitGroupingExpr(const Grouping *expr) const = 0;
  virtual std::any visitUnaryExpr(const Unary *expr) const = 0;
  virtual std::any visitBinaryExpr(const Binary *expr) const = 0;
  virtual std::any visitTernaryExpr(const Ternary *expr) const = 0;
};

struct Expr {
  virtual std::any accept(const Visitor &visitor) = 0;
};

struct Literal : Expr {
  std::optional<std::variant<std::string, double>> value;

  Literal() : value(std::nullopt) {};
  Literal(double v) : value(v) {};
  Literal(std::string v) : value(v) {};

  template <typename T> T accept(const Visitor &visitor) {
    return visitor.visitLiteralExpr(this);
  };
};

struct Grouping : Expr {
  std::unique_ptr<Expr> expr;

  Grouping(std::unique_ptr<Expr> e) : expr(std::move(e)) {};

  template <typename T> T accept(const Visitor &visitor) {
    return visitor.visitGroupingExpr(this);
  };
};

struct Unary : Expr {
  const Token op;
  std::unique_ptr<Expr> expr;

  Unary(Token o, std::unique_ptr<Expr> e) : op(o), expr(std::move(e)) {};

  template <typename T> T accept(const Visitor &visitor) {
    return visitor.visitUnaryExpr(this);
  };
};

struct Binary : Expr {
  std::unique_ptr<Expr> left;
  std::unique_ptr<Expr> right;
  const Token op;

  Binary(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r, Token o)
      : left(std::move(l)), right(std::move(r)), op(o) {};

  template <typename T> T accept(const Visitor &visitor) {
    return visitor.visitBinaryExpr(this);
  };
};

struct Ternary : Expr {
  std::unique_ptr<Expr> condition;
  std::unique_ptr<Expr> first;
  std::unique_ptr<Expr> second;

  Ternary(std::unique_ptr<Expr> c, std::unique_ptr<Expr> f,
          std::unique_ptr<Expr> s)
      : condition(std::move(c)), first(std::move(f)), second(std::move(s)) {};

  template <typename T> T accept(const Visitor &visitor) {
    return visitor.visitTernaryExpr(this);
  };
};

#endif
