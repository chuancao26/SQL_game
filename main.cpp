#include <iostream>
#include "Lexico.cpp"
#include "Sintactico.cpp"
int main()
{
  std::string query = "SELECT name, age FROM users WHERE age >= 21 ORDER BY name DESC";
  std::vector<Token> tokens = tokenize(query);
  
  std::cout << "Matriz de tokens:" << std::endl;
  for (const auto& token : tokens)
  {
    std::cout << token.value << " - " << tokenNames[token.type] << std::endl;
  }
  Parser parser(tokens);
  Node* ast = parser.parse();
  
  print_ast(ast);
  return 0;
}
