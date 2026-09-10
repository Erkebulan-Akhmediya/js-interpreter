#include "expr.h"
#include <algorithm>
#include <optional>
#include <string>
#include <variant>

template <typename T>
Literal<T>::Literal(std::variant<std::string, double> v) : value(v) {};

template <typename T> T Literal<T>::accept(const Visitor<T> &visitor) {
  visitor.visitLiteralExpr(*this);
};

template <typename T>
Grouping<T>::Grouping(std::unique_ptr<Expr<T>> e) : expr(std::move(e)) {};

template <typename T> T Grouping<T>::accept(const Visitor<T> &visitor) {
  visitor.visitGroupingExpr(*this);
};

template <typename T>
Unary<T>::Unary(Token o, std::unique_ptr<Expr<T>> e)
    : op(o), expr(std::move(e)) {};

template <typename T> T Unary<T>::accept(const Visitor<T> &visitor) {
  visitor.visitUnaryExpr(*this);
};

template <typename T>
Binary<T>::Binary(std::unique_ptr<Expr<T>> l, std::unique_ptr<Expr<T>> r,
                  Token o)
    : left(std::move(l)), right(std::move(r)), op(o) {};

template <typename T> T Binary<T>::accept(const Visitor<T> &visitor) {
  visitor.visitBinaryExpr(*this);
};

template <typename T>
Ternary<T>::Ternary(std::unique_ptr<Expr<T>> c, std::unique_ptr<Expr<T>> f,
                    std::unique_ptr<Expr<T>> s)
    : condition(std::move(c)), first(std::move(f)), second(std::move(s)) {};

template <typename T> T Ternary<T>::accept(const Visitor<T> &visitor) {
  visitor.visitTernaryExpr(*this);
};
