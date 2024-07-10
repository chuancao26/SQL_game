#include "Parser.h"
void Parser::print_ast (Node* node, int level = 0)
{
  for (int i = 0; i < level; ++i)
    cout << "  ";
  cout << node->type;
  if (!node->value.empty ())
    cout << ": " << node->value;
  cout << endl;
  for (Node* child : node->children)
    {
      print_ast (child, level + 1);
    }
}

Parser::Parser (const vector<Token>& tokens) : tokens (tokens), current (0) {}

Node* Parser::parse ()
{
  return query ();
}

Token& Parser::consume ()
{
  return tokens[current++];
}

Token& Parser::peek ()
{
  return tokens[current];
}

bool Parser::match (TokenType type)
{
  if (current < tokens.size () && tokens[current].type == type)
    {
      return true;
    }
  return false;
}

Node* Parser::query ()
{
  Node* node = new Node ("QUERY");
  if (match (SELECT))
    {
      consume ();
      node->children.push_back (select_list ());
      if (match (FROM))
        {
          consume ();
          node->children.push_back (table_list ());
          node->children.push_back (where_clause ());
          node->children.push_back (order_clause ());
        }
    }
  return node;
}

Node* Parser::select_list ()
{
  Node* node = new Node ("SELECT_LIST");
  if (match (ASTERISK))
    {
      node->children.push_back (new Node ("COLUMN", consume ().value));
    }
  else
    {
      node->children.push_back (column ());
      while (match (COMMA))
        {
          consume ();
          node->children.push_back (column ());
        }
    }
  return node;
}

Node* Parser::column ()
{
  Node* node = new Node ("COLUMN");
  Node* identifier1 = new Node ("IDENTIFIER", consume ().value);
  node->children.push_back (identifier1);
  if (match (DOT))
    {
      consume ();
      Node* identifier2 = new Node ("IDENTIFIER", consume ().value);
      node->children.push_back (identifier2);
    }
  return node;
}

Node* Parser::table_list ()
{
  Node* node = new Node ("TABLE_LIST");
  node->children.push_back (table ());
  while (match (COMMA))
    {
      consume ();
      node->children.push_back (table ());
    }
  return node;
}

Node* Parser::table ()
{
  return new Node ("TABLE", consume ().value);
}

Node* Parser::where_clause ()
{
  Node* node = new Node ("WHERE_CLAUSE");
  if (match (WHERE))
    {
      consume ();
      node->children.push_back (condition ());
    }
  return node;
}

Node* Parser::condition ()
{
  Node* node = new Node ("CONDITION");
  node->children.push_back (expression ());
  if (match (EQUALS) || match (NOT_EQUALS) || match (LESS_THAN) || match (GREATER_THAN) || match (LESS_EQUALS) || match (GREATER_EQUALS))
    {
      node->children.push_back (new Node ("OPERATOR", consume ().value));
      node->children.push_back (expression ());
    }
  else if (match (AND) || match (OR))
    {
      node->children.push_back (new Node ("LOGICAL_OPERATOR", consume ().value));
      node->children.push_back (condition ());
    }
  else if (match (OPEN_PAREN))
    {
      consume ();
      node->children.push_back (condition ());
      consume (); // consume CLOSE_PAREN
    }
  return node;
}

Node* Parser::expression ()
{
  Node* node = new Node ("EXPRESSION");
  if (match (IDENTIFIER))
    {
      node->children.push_back (new Node ("IDENTIFIER", consume ().value));
    }
  else if (match (LITERAL))
    {
      node->children.push_back (new Node ("LITERAL", consume ().value));
    }
  return node;
}

Node* Parser::order_clause ()
{
  Node* node = new Node ("ORDER_CLAUSE");
  if (match (ORDER_BY))
    {
      consume ();
      node->children.push_back (order_list ());
    }
  return node;
}

Node* Parser::order_list ()
{
  Node* node = new Node ("ORDER_LIST");
  node->children.push_back (order_item ());
  while (match (COMMA))
    {
      consume ();
      node->children.push_back (order_item ());
    }
  return node;
}

Node* Parser::order_item ()
{
  Node* node = new Node ("ORDER_ITEM");
  node->children.push_back (new Node ("IDENTIFIER", consume ().value));
  if (match (ASC) || match (DESC))
    {
      node->children.push_back (new Node ("ORDER", consume ().value));
    }
  return node;
}

