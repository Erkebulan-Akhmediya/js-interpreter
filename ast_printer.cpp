#include "expr.h"
#include "token.h"
#include <memory>
#include <optional>
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
  std::string print(Expr<std::string> *expr) { return expr->accept(*this); }

  std::string visitLiteralExpr(const Literal<std::string> *expr) const {
    if (!expr->value.has_value()) {
      return "null";
    }

    if (auto val = std::get_if<std::string>(&expr->value.value())) {
      return *val;
    }

    // there is no nullptr check, since at this point it is guaranteed to be a
    // double
    return std::to_string(*std::get_if<double>(&expr->value.value()));
  }

  std::string visitGroupingExpr(const Grouping<std::string> *expr) const {
    return parenthesize("group",
                        std::vector<Expr<std::string> *>{expr->expr.get()});
  }

  std::string visitUnaryExpr(const Unary<std::string> *expr) const {
    return parenthesize(std::string(expr->op.lexeme), {expr->expr.get()});
  }

  std::string visitBinaryExpr(const Binary<std::string> *expr) const {
    return parenthesize(std::string(expr->op.lexeme),
                        {expr->left.get(), expr->right.get()});
  }

  std::string visitTernaryExpr(const Ternary<std::string> *expr) const {
    return parenthesize("ternary", {expr->condition.get(), expr->first.get(),
                                    expr->second.get()});
  }
};

// just to test
// #include <iostream>
//
// int main() {
//   auto hundred23 = std::make_unique<Literal<std::string>>(123);
//   Token minus(TokenType::MINUS, "-", std::nullopt);
//   auto minus123 =
//       std::make_unique<Unary<std::string>>(minus, std::move(hundred23));

//   auto fourty5 = std::make_unique<Literal<std::string>>(45.32);
//   auto group45 = std::make_unique<Grouping<std::string>>(std::move(fourty5));
//   Token star(TokenType::STAR, "*", std::nullopt);
//   auto expr = std::make_unique<Binary<std::string>>(std::move(minus123),
//                                                     std::move(group45),
//                                                     star);
//   std::cout << AstPrinter().print(expr.get());
// }
