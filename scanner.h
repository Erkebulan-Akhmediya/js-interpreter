#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <string>
#include <unordered_map>
#include <vector>

class Scanner {
private:
  const static std::unordered_map<std::string, TokenType> keywords;

  std::string_view source;
  std::vector<Token> tokens;
  size_t start = 0;
  size_t current = 0;

  void scanToken();
  void addToken(TokenType type);
  void addToken(TokenType type,
                std::optional<std::variant<std::string_view, double>> literal);

  char advance();
  char peek();
  char peekNext();
  bool match(char expected);

  void string();
  void number();
  void identifier();

  bool is_at_end();
  inline bool isDigit(char c);
  inline bool isAlpha(char c);

public:
  Scanner(std::string_view p_source);
  std::vector<Token> scanTokens();
};

#endif
