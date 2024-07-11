#include <iostream>
#include "Analyzers.cpp"
#include "Controller.cpp"
using namespace std;

int main() {
    string query;
    getline(cin, query);
    Analyzer analizador;
    if(analizador.getStatus(query))
    {
      Controller controller;
      controller.run();
    }

    /*
    std::vector<Token> tokens = tokenize(query);

    try {
        // Parser
        Parser parser(tokens);
        Node* ast = parser.parse();
        parser.print_ast(ast);

        if (validate_ast(ast)) {
            std::cout << "La consulta es semanticamente valida." << std::endl;
        } else {
            std::cout << "La consulta tiene errores semanticos." << std::endl;
        }
    }
    catch (const SyntaxError& e)
    {
      std::cout << "Syntax error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) 
    {
      std::cout << "An error occurred: " << e.what() << std::endl;
    }
    */
    return 0;
}

