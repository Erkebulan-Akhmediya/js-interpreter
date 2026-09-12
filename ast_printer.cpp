#include "ast_printer.h"
#include "expr.h"
#include "token.h"
#include <any>
#include <optional>
#include <string>
#include <variant>
#include <vector>

std::string AstPrinter::parenthesize(std::string name,
                                     std::vector<Expr *> exprs) const {
  std::string node = "(" + name;
  for (auto expr : exprs) {
    node += " " + std::any_cast<std::string>(expr->accept(*this));
  }
  node += ")";
  return node;
};

std::string AstPrinter::print(Expr *expr) {
  return std::any_cast<std::string>(expr->accept(*this));
}

std::any AstPrinter::visitLiteralExpr(const Literal *expr) const {
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

std::any AstPrinter::visitGroupingExpr(const Grouping *expr) const {
  return parenthesize("group", std::vector<Expr *>{expr->expr.get()});
}

std::any AstPrinter::visitUnaryExpr(const Unary *expr) const {
  return parenthesize(std::string(expr->op.lexeme), {expr->expr.get()});
}

std::any AstPrinter::visitBinaryExpr(const Binary *expr) const {
  return parenthesize(std::string(expr->op.lexeme),
                      {expr->left.get(), expr->right.get()});
}

std::any AstPrinter::visitTernaryExpr(const Ternary *expr) const {
  return parenthesize("ternary", {expr->condition.get(), expr->first.get(),
                                  expr->second.get()});
}

// just to test
// #include <iostream>

// int main() {
//   auto hundred23 = std::make_unique<Literal>(123);
//   Token minus(TokenType::MINUS, "-", std::nullopt);
//   auto minus123 = std::make_unique<Unary>(minus, std::move(hundred23));

//   auto fourty5 = std::make_unique<Literal>(45.32);
//   auto group45 = std::make_unique<Grouping>(std::move(fourty5));
//   Token star(TokenType::STAR, "*", std::nullopt);
//   auto expr =
//       std::make_unique<Binary>(std::move(minus123), std::move(group45),
//       star);
//   std::cout << AstPrinter().print(expr.get());
// }
