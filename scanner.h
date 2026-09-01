#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <string>
#include <vector>

class Scanner {
private:
  std::string source;
  std::vector<Token> tokens;
  int start = 0;
  int current = 0;

  bool is_at_end();

public:
  Scanner(std::string p_source);
  std::vector<Token> scanTokens();
};

#endif
