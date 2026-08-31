#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum class TokenType {
  // single char tokens
  EQ,
  SEMICOL,

  // multi char tokens

  // literals
  STR,
  NUM,

  // keywords
  LET
};

void run(std::stringstream &source) {
  std::cout << "out: " << source.str() << '\n';
}

void runFile(std::string path) {
  std::stringstream ss;
  ss << std::ifstream(path).rdbuf();
  run(ss);
}

void runPrompt() {
  for (std::string line; std::getline(std::cin, line);) {
    std::stringstream ss;
    ss << line;
    run(ss);
  }
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cout << "usage: js [script]\n";
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }
}
