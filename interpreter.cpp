#include "interpreter.h"
#include "expr.h"
#include "token.h"
#include <any>
#include <string>

std::any Interpreter::visitLiteralExpr(const Literal *expr) const {
  return expr->value;
}

std::any Interpreter::visitGroupingExpr(const Grouping *expr) const {
  return eval(expr->expr.get());
}

std::any Interpreter::visitUnaryExpr(const Unary *expr) const {
  std::any res = eval(expr->expr.get());
  switch (expr->op.type) {
  case TokenType::MINUS:
    return -std::any_cast<double>(res);
  default:
    return 0;
  }
}

std::any Interpreter::eval(Expr *expr) const { return expr->accept(*this); }

bool Interpreter::isTruthy(std::any val) const {
  if (auto v = std::any_cast<double>(&val))
    return *v != 0;

  if (auto v = std::any_cast<std::string>(&val))
    if (*v == "true" || *v != "")
      return true;

  return false;
};
