#ifndef INTERPRETER
#define INTERPRETER

#include "expr.h"
#include <any>

struct Interpreter : Visitor {
  std::any visitLiteralExpr(const Literal *expr) const;
  std::any visitGroupingExpr(const Grouping *expr) const;
  std::any visitUnaryExpr(const Unary *expr) const;
  std::any visitBinaryExpr(const Binary *expr) const;
  std::any visitTernaryExpr(const Ternary *expr) const;

  std::any eval(Expr *expr) const;
  bool isTruthy(std::any val) const;
};

#endif
