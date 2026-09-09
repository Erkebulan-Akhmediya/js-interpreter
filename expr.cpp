#include "token.h"
#include <string>
#include <variant>

struct Literal;
struct Grouping;
struct Unary;
struct Binary;
struct Ternary;

struct Visitor {
  virtual void visitLiteralExpr(const Literal *const expr) const = 0;
  virtual void visitGroupingExpr(const Grouping *const expr) const = 0;
  virtual void visitUnaryExpr(const Unary *const expr) const = 0;
  virtual void visitBinaryExpr(const Binary *const expr) const = 0;
  virtual void visitTernaryExpr(const Ternary *const expr) const = 0;
};

struct Expr {
  virtual void accept(const Visitor &visitor) = 0;
};

struct Literal : Expr {
  std::variant<std::string, double> value;

  Literal(std::variant<std::string, double> v) : value(v) {};

  void accept(const Visitor &visitor) override {
    visitor.visitLiteralExpr(this);
  };
};

struct Grouping : Expr {
  const Expr &expr;

  Grouping(const Expr &e) : expr(e) {};

  void accept(const Visitor &visitor) override {
    visitor.visitGroupingExpr(this);
  };
};

struct Unary : Expr {
  const Token op;
  const Expr &expr;

  Unary(Token o, const Expr &e) : op(o), expr(e) {};

  void accept(const Visitor &visitor) override {
    visitor.visitUnaryExpr(this);
  };
};

struct Binary : Expr {
  const Expr &left;
  const Expr &right;
  const Token op;

  Binary(const Expr &l, const Expr &r, Token o) : left(l), right(r), op(o) {};

  void accept(const Visitor &visitor) override {
    visitor.visitBinaryExpr(this);
  };
};

struct Ternary : Expr {
  const Expr &condition;
  const Expr &first;
  const Expr &second;

  Ternary(const Expr &c, const Expr &f, const Expr &s)
      : condition(c), first(f), second(s) {};

  void accept(const Visitor &visitor) override {
    visitor.visitTernaryExpr(this);
  };
};
