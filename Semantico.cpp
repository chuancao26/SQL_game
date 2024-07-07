#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <regex>
#include "Parser.cpp"

enum DataType {
    INTEGER,
    STRING,
    FLOAT,
    UNKNOWN_TYPE
};

// Definición del esquema de la base de datos
std::unordered_map<std::string, std::unordered_map<std::string, DataType>> databaseSchema = {
    {"producto", {{"nombre", STRING}, {"descripcion", STRING}, {"precio", FLOAT}}},
    {"orden", {{"id", INTEGER}, {"user_id", INTEGER}, {"amount", FLOAT}, {"date", STRING}}},
    {"persona", {{"nombre", STRING}, {"apellidos", STRING}, {"dni", STRING}}},
    {"users", {{"name", STRING}, {"age", INTEGER}}}
};

void obtenerCondicion(Node* conditionNode, std::vector<std::tuple<std::string, std::string, std::string>>& condiciones) {
    if (conditionNode->children.size() == 3) {
        Node* expression1 = conditionNode->children[0];
        Node* operatorNode = conditionNode->children[1];
        Node* expression2 = conditionNode->children[2];
        
        if (expression1->type == "EXPRESSION" && expression2->type == "EXPRESSION" && operatorNode->type == "OPERATOR") {
            std::string columna;
            std::string valor;
            
            for (auto expChild : expression1->children) {
                if (expChild->type == "IDENTIFIER") {
                    columna = expChild->value;
                }
            }
            
            for (auto expChild : expression2->children) {
                if (expChild->type == "IDENTIFIER" || expChild->type == "LITERAL") {
                    valor = expChild->value;
                }
            }
            
            condiciones.push_back(std::make_tuple(columna, operatorNode->value, valor));
        }
    }
}

void obtenerOrden(Node* orderClauseNode, std::vector<std::string>& ordenColumnas) {
    for (auto orderItemNode : orderClauseNode->children) {
        if (orderItemNode->type == "ORDER_ITEM") {
            for (auto identifierNode : orderItemNode->children) {
                if (identifierNode->type == "IDENTIFIER") {
                    std::string columnName = identifierNode->value;
                    ordenColumnas.push_back(columnName);
                }
            }
        }
    }
}


bool validate_ast(Node* ast) {
    if (!ast) {
        return false; // Si el nodo es nulo, no se puede verificar
    }
    
    std::string tabla;
    std::vector<std::string> columnas;
    std::vector<std::tuple<std::string, std::string, std::string>> condiciones;
    std::vector<std::string> ordenColumnas;
    
    // Recorrer los hijos del nodo raíz (QUERY)
    for (auto child : ast->children) {
        if (child->type == "TABLE_LIST") {
            // Recorrer las tablas especificadas en TABLE_LIST
            for (auto tableNode : child->children) {
                if (tableNode->type == "TABLE") {
                    tabla = tableNode->value; // Obtener el nombre de la tabla
                    // Verificar si la tabla existe en el esquema
                    auto it = databaseSchema.find(tabla);
                    if (it == databaseSchema.end()) {
                        std::cout << "Error: La tabla '" << tabla << "' no existe en el esquema." << std::endl;
                        return false;
                    }
                }
            }
        } else if (child->type == "SELECT_LIST") {
            // Recorrer las columnas especificadas en SELECT_LIST
            for (auto columnNode : child->children) {
                if (columnNode->type == "COLUMN") {
                    // Obtener el nombre de la columna
                    std::string columnName;
                    for (auto identifierNode : columnNode->children) {
                        if (identifierNode->type == "IDENTIFIER") {
                            columnName = identifierNode->value;
                            columnas.push_back(columnName);
                        }
                    }
                }
            }
        } else if (child->type == "WHERE_CLAUSE") {
            // Recorrer la cláusula WHERE y obtener las condiciones
            for (auto conditionNode : child->children) {
                if (conditionNode->type == "CONDITION") {
                    obtenerCondicion(conditionNode, condiciones);
                }
            }
        } else if (child->type == "ORDER_CLAUSE") {
            // Recorrer la cláusula ORDER BY y obtener las columnas
            obtenerOrden(child, ordenColumnas);
        }
    }
    
    // Verificar la existencia de cada columna en la tabla
    const auto& columnasEsquema = databaseSchema.at(tabla);
    for (const auto& columna : columnas) {
        auto colIt = columnasEsquema.find(columna);
        if (colIt == columnasEsquema.end()) {
            std::cout << "Error: La columna '" << columna << "' no existe en la tabla '" << tabla << "'." << std::endl;
            return false;
        }
    }

    for (const auto& condicion : condiciones) {
        std::string columna = std::get<0>(condicion);
        std::string operador = std::get<1>(condicion);
        std::string valor = std::get<2>(condicion);
        
        auto colIt = columnasEsquema.find(columna);
        if (colIt != columnasEsquema.end()) {
            DataType tipoDato = colIt->second;
            if ((tipoDato == INTEGER || tipoDato == FLOAT) && operador != "=" && operador != "!=") {
                std::regex numericRegex("^[0-9]+(\\.[0-9]+)?$");
                if (!std::regex_match(valor, numericRegex)) {
                    std::cout << "Error: No se puede realizar una comparacion numerica en la columna '" << columna << "' con el valor '" << valor << "' porque el valor no es numerico." << std::endl;
                    return false;
                }
            }
        } else {
            std::cout << "Error: La columna '" << columna << "' no existe en la tabla '" << tabla << "'." << std::endl;
            return false;
        }
    }

    // Verificar la existencia de cada columna en la cláusula ORDER BY
    for (const auto& columna : ordenColumnas) {
        auto colIt = columnasEsquema.find(columna);
        if (colIt == columnasEsquema.end()) {
            std::cout << "Error: La columna '" << columna << "' no existe en la tabla '" << tabla << "'." << std::endl;
            return false;
        }
    }
    
    // Si todo está bien, la consulta es válida
    return true;
}