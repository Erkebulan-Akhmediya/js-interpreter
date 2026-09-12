#ifndef AST_PRINTER
#define AST_PRINTER

#include "expr.h"
#include <vector>

class AstPrinter : Visitor {
private:
  std::string parenthesize(std::string name, std::vector<Expr *> exprs) const;

public:
  std::string print(Expr *expr);

  std::any visitLiteralExpr(const Literal *expr) const;

  std::any visitGroupingExpr(const Grouping *expr) const;

  std::any visitUnaryExpr(const Unary *expr) const;

  std::any visitBinaryExpr(const Binary *expr) const;

  std::any visitTernaryExpr(const Ternary *expr) const;
};

#endif
