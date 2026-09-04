#include "scanner.h"
#include "token.h"
#include <string>
#include <vector>

Scanner::Scanner(std::string p_source) : source(p_source) {}

bool Scanner::is_at_end() { return current >= source.size(); }

std::vector<Token> Scanner::scanTokens() {
  while (!is_at_end()) {
    start = current;
    scanToken();
  }
  tokens.push_back({TokenType::END, "", nullptr});
  return tokens;
}
