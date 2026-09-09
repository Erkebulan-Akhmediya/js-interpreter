#include "expr.h"
#include <optional>
#include <string>
#include <variant>

template <typename T>
Literal<T>::Literal(std::variant<std::string, double> v) : value(v) {};

template <typename T> T Literal<T>::accept(const Visitor<T> &visitor) {
  visitor.visitLiteralExpr(*this);
};

template <typename T> Grouping<T>::Grouping(const Expr<T> &e) : expr(e) {};

template <typename T> T Grouping<T>::accept(const Visitor<T> &visitor) {
  visitor.visitGroupingExpr(*this);
};

template <typename T>
Unary<T>::Unary(Token o, const Expr<T> &e) : op(o), expr(e) {};

template <typename T> T Unary<T>::accept(const Visitor<T> &visitor) {
  visitor.visitUnaryExpr(*this);
};

template <typename T>
Binary<T>::Binary(const Expr<T> &l, const Expr<T> &r, Token o)
    : left(l), right(r), op(o) {};

template <typename T> T Binary<T>::accept(const Visitor<T> &visitor) {
  visitor.visitBinaryExpr(*this);
};

template <typename T>
Ternary<T>::Ternary(const Expr<T> &c, const Expr<T> &f, const Expr<T> &s)
    : condition(c), first(f), second(s) {};

template <typename T> T Ternary<T>::accept(const Visitor<T> &visitor) {
  visitor.visitTernaryExpr(*this);
};
