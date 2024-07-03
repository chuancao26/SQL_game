#include <iostream>
#include "Parser.cpp"
#include "Vista.cpp"
using namespace std;
int main()
{
  std::string query = "SELECT name, age FROM users WHERE age >= 21 ORDER BY name DESC";
  std::vector<Token> tokens = tokenize(query);
  
  std::cout << "Matriz de tokens:" << std::endl;
  for (const auto& token : tokens)
  {
    std::cout << token.value << " - " << tokenNames[token.type] << std::endl;
  }
  // Parser
  Parser parser(tokens);
  Node* ast = parser.parse();
  parser.print_ast(ast);
  
  // view Game
  Vista view;
  view.ejecutar();
  return 0;
}
