#include <iostream>
#include "Semantico.cpp"
#include "Controller.cpp"
//#include "Controller2.cpp"
using namespace std;
int main()
{
  std::string query = "SELECT namesss, age FROM users WHERE age >= 21 ORDER BY name DESC";
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
  
  if (validate_ast(ast)) {
      std::cout << "La consulta es semanticamente valida." << std::endl;
  } else {
      std::cout << "La consulta tiene errores semanticos." << std::endl;
  }
  // view Game
  Controller controller;
  controller.run();
  //int n = 2; // Define el tamaño de la cuadrícula
  //Controller2 controller2(n);
  //controller2.run();
  return 0;
}
