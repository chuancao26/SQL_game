#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "Lexico.cpp"

using namespace std;

struct Node
{
  string type;
  string value;
  vector<Node*> children;

  Node(string type, string value = "") : type(type), value(value) {}
};

void print_ast(Node* node, int level = 0);

class Parser
{
  vector<Token> tokens;
  size_t current;
public:
  Parser(const vector<Token>& tokens);
  Node* parse();
  void print_ast(Node*, int);

private:
  Token& consume();
  Token& peek();
  bool match(TokenType type);
  Node* query();
  Node* select_list();
  Node* column();
  Node* table_list();
  Node* table();
  Node* where_clause();
  Node* condition();
  Node* expression();
  Node* order_clause();
  Node* order_list();
  Node* order_item();
};

#endif // PARSER_H

