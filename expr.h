#ifndef EXPR
#define EXPR

#include "token.h"
#include <optional>
#include <string>
#include <variant>

template <typename T> struct Literal;
template <typename T> struct Grouping;
template <typename T> struct Unary;
template <typename T> struct Binary;
template <typename T> struct Ternary;

template <typename T> struct Visitor {
  virtual T visitLiteralExpr(const Literal<T> &expr) const = 0;
  virtual T visitGroupingExpr(const Grouping<T> &expr) const = 0;
  virtual T visitUnaryExpr(const Unary<T> &expr) const = 0;
  virtual T visitBinaryExpr(const Binary<T> &expr) const = 0;
  virtual T visitTernaryExpr(const Ternary<T> &expr) const = 0;
};

template <typename T> struct Expr {
  virtual T accept(const Visitor<T> &visitor) = 0;
};

template <typename T> struct Literal : Expr<T> {
  std::optional<std::variant<std::string, double>> value;

  Literal(std::variant<std::string, double> v);

  T accept(const Visitor<T> &visitor) override;
};

template <typename T> struct Grouping : Expr<T> {
  const Expr<T> &expr;

  Grouping(const Expr<T> &e);

  T accept(const Visitor<T> &visitor) override;
};

template <typename T> struct Unary : Expr<T> {
  const Token op;
  const Expr<T> &expr;

  Unary(Token o, const Expr<T> &e);

  T accept(const Visitor<T> &visitor) override;
};

template <typename T> struct Binary : Expr<T> {
  const Expr<T> &left;
  const Expr<T> &right;
  const Token op;

  Binary(const Expr<T> &l, const Expr<T> &r, Token o);

  T accept(const Visitor<T> &visitor) override;
};

template <typename T> struct Ternary : Expr<T> {
  const Expr<T> &condition;
  const Expr<T> &first;
  const Expr<T> &second;

  Ternary(const Expr<T> &c, const Expr<T> &f, const Expr<T> &s);

  T accept(const Visitor<T> &visitor) override;
};

#endif
