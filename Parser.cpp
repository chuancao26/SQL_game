#include "Parser.h"
#include <exception>
#include <string>
#include <cctype>
#include <algorithm>

class SyntaxError : public std::exception {
public:
    SyntaxError(const std::string& message) : message(message) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

void Parser::print_ast(Node* node, int level)
{
    for (int i = 0; i < level; ++i)
        cout << "  ";
    cout << node->type;
    if (!node->value.empty())
        cout << ": " << node->value;
    cout << endl;
    for (Node* child : node->children)
    {
        print_ast(child, level + 1);
    }
}

Parser::Parser(const vector<Token>& tokens) : tokens(tokens), current(0) {}

Node* Parser::parse()
{
    return query();
}

Token& Parser::consume()
{
  std::cout << tokens[current].value << std::endl;
    return tokens[current++];
}

Token& Parser::peek()
{
    return tokens[current];
}

bool Parser::match(TokenType type)
{
    if (current < tokens.size() && tokens[current].type == type)
    {
        return true;
    }
    return false;
}

bool Parser::isValidIdentifier(const std::string& id) {
    if (id.empty() || !std::isalpha(id[0])) {
        return false;
    }
    return std::all_of(id.begin() + 1, id.end(), [](char c) {
        return std::isalnum(c) || c == '_';
    });
}

Node* Parser::query() {
    Node* node = new Node("QUERY");
    if (match(SELECT)) {
        consume();
        node->children.push_back(select_list());
        if (match(FROM)) {
            consume();
            node->children.push_back(table_list());
            node->children.push_back(where_clause());
            node->children.push_back(order_clause());
        } else {
            throw SyntaxError("Expected 'FROM' after 'SELECT' clause");
        }
    } else {
        throw SyntaxError("Expected 'SELECT' at the beginning of the query");
    }
    return node;
}

Node* Parser::select_list()
{
    Node* node = new Node("SELECT_LIST");
    if (match(ASTERISK))
    {
        node->children.push_back(new Node("COLUMN", consume().value));
    }
    else
    {
        node->children.push_back(column());
        while (match(COMMA))
        {
            consume();
            node->children.push_back(column());
        }
    }
    return node;
}

Node* Parser::column()
{
    Node* node = new Node("COLUMN");
    if (match(IDENTIFIER)) {
        Token idToken = consume();
        if (!isValidIdentifier(idToken.value)) {
            throw SyntaxError("Invalid identifier: " + idToken.value);
        }
        Node* identifier1 = new Node("IDENTIFIER", idToken.value);
        node->children.push_back(identifier1);
        if (match(DOT))
        {
            consume();
            if (match(IDENTIFIER)) {
                idToken = consume();
                if (!isValidIdentifier(idToken.value)) {
                    throw SyntaxError("Invalid identifier: " + idToken.value);
                }
                Node* identifier2 = new Node("IDENTIFIER", idToken.value);
                node->children.push_back(identifier2);
            } else {
                throw SyntaxError("Expected identifier after '.'");
            }
        }
    } else {
        throw SyntaxError("Expected identifier");
    }
    return node;
}

Node* Parser::table_list()
{
    Node* node = new Node("TABLE_LIST");
    node->children.push_back(table());
    while (match(COMMA))
    {
        consume();
        node->children.push_back(table());
    }
    return node;
}

Node* Parser::table()
{
    if (match(IDENTIFIER)) {
        Token idToken = consume();
        if (!isValidIdentifier(idToken.value)) {
            throw SyntaxError("Invalid table name: " + idToken.value);
        }
        return new Node("TABLE", idToken.value);
    } else {
        throw SyntaxError("Invalid table name.");
    }
}

Node* Parser::where_clause()
{
    Node* node = new Node("WHERE_CLAUSE");
    if (match(WHERE))
    {
        consume();
        node->children.push_back(condition());
    }
    else
    {
      throw SyntaxError("Invalid expression around WHERE clause.");
    }
    return node;
}

Node* Parser::condition()
{
    Node* node = new Node("CONDITION");
    node->children.push_back(expression());
    if (match(EQUALS) || match(NOT_EQUALS) || match(LESS_THAN) || match(GREATER_THAN) || match(LESS_EQUALS) || match(GREATER_EQUALS))
    {
        node->children.push_back(new Node("OPERATOR", consume().value));
        node->children.push_back(expression());
    }
    else if (match(AND) || match(OR))
    {
        node->children.push_back(new Node("LOGICAL_OPERATOR", consume().value));
        node->children.push_back(condition());
    }
    else if (match(OPEN_PAREN))
    {
        consume();
        node->children.push_back(condition());
        consume();
    }
    return node;
}

Node* Parser::expression()
{
    Node* node = new Node("EXPRESSION");
    if (match(IDENTIFIER))
    {
        Token idToken = consume();
        if (!isValidIdentifier(idToken.value)) {
            throw SyntaxError("Invalid identifier in expression: " + idToken.value);
        }
        node->children.push_back(new Node("IDENTIFIER", idToken.value));
    }
    else if (match(LITERAL))
    {
        node->children.push_back(new Node("LITERAL", consume().value));
    }
    else
    {
      throw SyntaxError("Missing expresions in WHEN clause");
    }
    return node;
}

Node* Parser::order_clause()
{
    Node* node = new Node("ORDER_CLAUSE");
    if (match(ORDER_BY))
    {
        consume();
	if (!match(ORDER_BY))
	{
	  throw SyntaxError("Invalid ORDER BY expression: ");
	}
	consume();
        node->children.push_back(order_list());
    }
    else
    {
      throw SyntaxError("Invalid expression next to ORDER BY clause");
    }
    return node;
}

Node* Parser::order_list()
{
    Node* node = new Node("ORDER_LIST");
    node->children.push_back(order_item());
    while (match(COMMA))
    {
        consume();
        node->children.push_back(order_item());
    }
    return node;
}

Node* Parser::order_item()
{
    Node* node = new Node("ORDER_ITEM");
    if (match(IDENTIFIER)) {
        Token idToken = consume();
        if (!isValidIdentifier(idToken.value)) {
            throw SyntaxError("Invalid identifier in ORDER BY: " + idToken.value);
        }
        node->children.push_back(new Node("IDENTIFIER", idToken.value));
        if (match(ASC) || match(DESC))
        {
            node->children.push_back(new Node("ORDER", consume().value));
        }
    } else {
        throw SyntaxError("Expected identifier in ORDER BY clause");
    }
    return node;
}
