#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/ExpressionNode.h"
#include "Parser/BinaryExpressionNode.h"
#include "Parser/ConstNode.h"

void PrettyPrint(Parser::AST::ExpressionNode* node, int level = 0)
{
    for (int i = 0; i < level; i++) std::cout << '\t';
    std::cout << ToString(node->Kind());
    if (node->Kind() == Parser::AST::NodeKind::CONST) std::cout << " " << ((Parser::AST::ConstNode*)node)->Value();
    std::cout << "\n";

    switch (node->Kind())
    {
    case Parser::AST::NodeKind::ADD:
    case Parser::AST::NodeKind::MULT:
    case Parser::AST::NodeKind::DIV:
    case Parser::AST::NodeKind::SUBTRACT:
        PrettyPrint(((Parser::AST::BinaryExpressionNode*)node)->OpLeft(), level + 1);
        PrettyPrint(((Parser::AST::BinaryExpressionNode*)node)->OpRight(), level + 1);
        break;
    case Parser::AST::NodeKind::UNARYMINUS:
        PrettyPrint(((Parser::AST::UnaryExpressionNode*)node)->Op(), level + 1);
        break;
    }
}

int main()
{
    std::string filePath = "C:\\GitHub_Repos\\PLTest\\input.txt";
    std::ifstream ifs(filePath);

    std::shared_ptr<Lexer::Lexer> lexer = std::make_shared<Lexer::Lexer>(ifs);
    std::shared_ptr<Parser::Parser> parser = std::make_shared<Parser::Parser>(lexer);
    

    Parser::AST::ExpressionNode* mainExpr = parser->ParseExpression();
    PrettyPrint(mainExpr);
}