#include "expr.h"
#include <string>
#include <variant>
#include <vector>

class AstPrinter : Visitor<std::string> {
private:
  std::string parenthesize(std::string name,
                           std::vector<Expr<std::string> *> exprs) const {
    std::string node = "(" + name;
    for (auto expr : exprs) {
      node += " " + expr->accept(*this);
    }
    node += ")";
    return node;
  };

public:
  std::string print(Expr<std::string> &expr) { return expr.accept(*this); }

  std::string visitLiteralExpr(const Literal<std::string> &expr) const {
    if (!expr.value.has_value()) {
      return "null";
    }

    if (auto val = std::get_if<std::string>(&expr.value.value())) {
      return *val;
    }

    // there is no nullptr check, since at this point it is guaranteed to be a
    // double
    return std::to_string(*std::get_if<double>(&expr.value.value()));
  }

  std::string visitGroupingExpr(const Grouping<std::string> &expr) const {
    return parenthesize("group",
                        std::vector<Expr<std::string> *>{expr.expr.get()});
  }

  std::string visitUnaryExpr(const Unary<std::string> &expr) const {
    return parenthesize(std::string(expr.op.lexeme), {expr.expr.get()});
  }

  std::string visitBinaryExpr(const Binary<std::string> &expr) const {
    return parenthesize(std::string(expr.op.lexeme),
                        {expr.left.get(), expr.right.get()});
  }

  std::string visitTernaryExpr(const Ternary<std::string> &expr) const {
    return parenthesize(
        "ternary", {expr.condition.get(), expr.first.get(), expr.second.get()});
  }
};
