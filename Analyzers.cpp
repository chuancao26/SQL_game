#include "Analyzers.h"
Analyzer::Analyzer(): message("Not defined")
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
    {
      message =  "La consulta tiene errores semanticos.";
      return 0;
    }
  }
  catch (const SyntaxError& e)
  {
    message = e.what();
    return 0;
  }
  catch (const std::exception& e) 
  {
    message = e.what();
    return 0;
  }
  return 1;
}
string Analyzer::getMessage()
{
  return message;
}
