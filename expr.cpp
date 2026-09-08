#include "token.h"
#include <string>
#include <variant>

struct Expr {};

struct Literal : Expr {
  std::variant<std::string, double> value;

  Literal(std::variant<std::string, double> v) : value(v) {}
};

struct Grouping : Expr {
  Expr expr;

  Grouping(Expr e) : expr(e) {}
};

struct Unary : Expr {
  const Token op;
  const Expr expr;

  Unary(Token o, Expr e) : op(o), expr(e) {};
};

struct Binary : Expr {
  const Expr left;
  const Expr right;
  const Token op;

  Binary(Expr l, Expr r, Token o) : left(l), right(r), op(o) {}
};

struct Ternary : Expr {
  const Expr condition;
  const Expr first;
  const Expr second;

  Ternary(Expr c, Expr f, Expr s) : condition(c), first(f), second(s) {}
};
