#include "Analyzers.h"
Analyzer::Analyzer()
{
}
bool Analyzer::getStatus(string query)
{
  tokens = tokenize(query);
  try 
  {
    Parser parser(tokens);
    Node* ast = parser.parse();
    //parser.print_ast(ast);

    if (!validate_ast(ast))
      return 0;
      /*
        std::cout << "La consulta es semanticamente valida." << std::endl;
    } else {
        std::cout << "La consulta tiene errores semanticos." << std::endl;
    }
    */
  }
  catch (const SyntaxError& e)
  {
    //status = e.what();
    return 0;
  }
  catch (const std::exception& e) 
  {
    //status = e.what();
    return 0;
  }
  return 1;
}
