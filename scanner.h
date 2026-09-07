#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <string>
#include <vector>

class Scanner {
private:
  std::string source;
  std::vector<Token> tokens;
  size_t start = 0;
  size_t current = 0;

  void scanToken();
  void addToken(TokenType type);
  void addToken(TokenType type, std::any literal);

  char advance();
  char peek();
  bool match(char expected);

  void string();

  bool is_at_end();

public:
  Scanner(std::string p_source);
  std::vector<Token> scanTokens();
};

#endif
