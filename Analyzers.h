#ifndef ANALYZERS_H
#define ANALYZERS_H
#include "Semantico.cpp"
#include "Parser.h" 
class Analyzer
{
  private:
    std::vector<Token> tokens;
    string message;
  public:
    Analyzer();
    bool getStatus(string);
    string getMessage();
};
#endif



