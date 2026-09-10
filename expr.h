#ifndef EXPR
#define EXPR

#include "token.h"
#include <memory>
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
  std::unique_ptr<Expr<T>> expr;

  Grouping(std::unique_ptr<Expr<T>> e);

  T accept(const Visitor<T> &visitor) override;
};

template <typename T> struct Unary : Expr<T> {
  const Token op;
  std::unique_ptr<Expr<T>> expr;

  Unary(Token o, std::unique_ptr<Expr<T>> e);

  T accept(const Visitor<T> &visitor) override;
};

template <typename T> struct Binary : Expr<T> {
  std::unique_ptr<Expr<T>> left;
  std::unique_ptr<Expr<T>> right;
  const Token op;

  Binary(std::unique_ptr<Expr<T>> l, std::unique_ptr<Expr<T>> r, Token o);

  T accept(const Visitor<T> &visitor) override;
};

template <typename T> struct Ternary : Expr<T> {
  std::unique_ptr<Expr<T>> condition;
  std::unique_ptr<Expr<T>> first;
  std::unique_ptr<Expr<T>> second;

  Ternary(std::unique_ptr<Expr<T>> c, std::unique_ptr<Expr<T>> f,
          std::unique_ptr<Expr<T>> s);

  T accept(const Visitor<T> &visitor) override;
};

#endif
