#include "scanner.h"
#include "token.h"
#include <any>
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

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
  case '=':
    addToken(match('=') ? TokenType::DOUBLE_EQ : TokenType::EQ);
    break;
  case '>':
    addToken(match('=') ? TokenType::GREATER_EQ : TokenType::GREATER);
    break;
  case '<':
    addToken(match('=') ? TokenType::LESS_EQ : TokenType::LESS);
    break;
  case '!':
    addToken(match('=') ? TokenType::EXCLAMATION_EQ : TokenType::EXCLAMATION);
    break;
  case ';':
    addToken(TokenType::SEMICOL);
    break;
  case '-':
    if (match('-'))
      addToken(TokenType::DECREMENT);
    else if (match('='))
      addToken(TokenType::MINUS_EQ);
    else
      addToken(TokenType::MINUS);
    break;
  case '+':
    if (match('+'))
      addToken(TokenType::INCREMENT);
    else if (match('='))
      addToken(TokenType::PLUS_EQ);
    else
      addToken(TokenType::PLUS);
    break;
  case '/':
    if (match('='))
      addToken(TokenType::SLASH_EQ);
    else if (match('/')) {
      while (peek() != '\n' && !is_at_end())
        advance();
    } else
      addToken(TokenType::SLASH);
    break;
  case '%':
    addToken(match('=') ? TokenType::PERCENT_EQ : TokenType::PERCENT);
    break;
  case '*':
    addToken(match('=') ? TokenType::STAR_EQ : TokenType::STAR);
    break;
  case ',':
    addToken(TokenType::COMMA);
    break;
  case '\'':
    addToken(TokenType::SINGLE_QUOTE);
    break;
  case '"':
    addToken(TokenType::DOUBLE_QUOTE);
    break;
  case '(':
    addToken(TokenType::LEFT_BRACET);
    break;
  case ')':
    addToken(TokenType::RIGHT_BRACET);
    break;
  case '{':
    addToken(TokenType::LEFT_CURLY_BRACET);
    break;
  case '}':
    addToken(TokenType::RIGHT_CURLY_BRACET);
    break;
  case '&':
    addToken(TokenType::AND);
    break;
  case '|':
    addToken(TokenType::OR);
    break;
  case ' ':
  case '\n':
  case '\t':
  case '\r':
    break;
  default:
    if (isDigit(c)) {
    }
  }
}

char Scanner::advance() { return source.at(current++); }

bool Scanner::match(char expected) {
  if (is_at_end())
    return false;
  if (source.at(current) != expected)
    return false;

  ++current;
  return true;
}

char Scanner::peek() {
  if (is_at_end())
    return '\0';
  return source.at(current);
}

char Scanner::peekNext() {
  if (current + 1 >= source.size())
    return '\0';
  return source.at(current + 1);
}

void Scanner::string() {
  while (peek() != '"') {
    advance();
    if (peek() != '\n' || is_at_end())
      return;
  }
  advance();

  std::string value = source.substr(start + 1, current - 1);
  addToken(TokenType::STR, value);
}

void Scanner::number() {
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    while (isDigit(peek()))
      advance();
  }
  addToken(TokenType::NUM, std::stod(source.substr(start, current)));
}

inline bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

void Scanner::addToken(TokenType type) { addToken(type, nullptr); }

void Scanner::addToken(TokenType type, std::any literal) {
  std::string text = source.substr(start, current);
  tokens.push_back({type, text, literal});
}
