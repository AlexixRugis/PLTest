#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include "Lexer.h"
#include "Parser.h"
#include "ExpressionNode.h"
#include "BinaryExpressionNode.h"
#include "ConstNode.h"

std::string ToString(Parser::AST::NodeKind kind)
{
    switch (kind)
    {
    case Parser::AST::NodeKind::CONST:
        return "Parser::AST::NodeKind::CONST";
    case Parser::AST::NodeKind::ADD:
        return "Parser::AST::NodeKind::ADD";
    case Parser::AST::NodeKind::SUBTRACT:
        return "Parser::AST::NodeKind::SUBTRACT";
    case Parser::AST::NodeKind::MULT:
        return "Parser::AST::NodeKind::MULT";
    case Parser::AST::NodeKind::DIV:
        return "Parser::AST::NodeKind::DIV";
    default:
        return "UNKNOWN";
    }
}

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