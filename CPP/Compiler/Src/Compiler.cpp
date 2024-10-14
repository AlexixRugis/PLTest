#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include "Diagnostic/Diagnostic.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/ExpressionNode.h"
#include "Parser/BinaryExpressionNode.h"
#include "Parser/ConstNode.h"
#include "Parser/VariableNode.h"

void PrettyPrint(Parser::AST::ExpressionNode* node, int level = 0)
{
    for (int i = 0; i < level; i++) std::cout << '\t';
    std::cout << ToString(node->Kind());
    if (node->Kind() == Parser::AST::Op::CONST)
    {
        std::cout << " " << ((Parser::AST::ConstNode*)node)->Value() << "\n";
        return;
    }
    else if (node->Kind() == Parser::AST::Op::ID)
    {
        std::cout << " " << ((Parser::AST::VariableNode*)node)->Name() << "\n";
        return;
    }
    std::cout << "\n";

    auto* binop = dynamic_cast<Parser::AST::BinaryExpressionNode*>(node);
    if (binop)
    {
        PrettyPrint(((Parser::AST::BinaryExpressionNode*)node)->OpLeft(), level + 1);
        PrettyPrint(((Parser::AST::BinaryExpressionNode*)node)->OpRight(), level + 1);
        return;
    }

    auto* unop = dynamic_cast<Parser::AST::UnaryExpressionNode*>(node);
    if (unop)
    {
        PrettyPrint(((Parser::AST::UnaryExpressionNode*)node)->Op(), level + 1);
        return;
    }

    switch (node->Kind())
    {
    case Parser::AST::Op::ADD:
    case Parser::AST::Op::MULT:
    case Parser::AST::Op::DIV:
    case Parser::AST::Op::SUBTRACT:
        PrettyPrint(((Parser::AST::BinaryExpressionNode*)node)->OpLeft(), level + 1);
        PrettyPrint(((Parser::AST::BinaryExpressionNode*)node)->OpRight(), level + 1);
        break;
    case Parser::AST::Op::UNARYMINUS:
        PrettyPrint(((Parser::AST::UnaryExpressionNode*)node)->Op(), level + 1);
        break;
    }
}

int main()
{
    std::string filePath = "C:\\GitHub_Repos\\PLTest\\input.txt";
    std::ifstream ifs(filePath);

    std::shared_ptr<Diagnostic::Diagnostic> diagnostic = std::make_shared<Diagnostic::Diagnostic>();
    std::shared_ptr<Lexer::Lexer> lexer = std::make_shared<Lexer::Lexer>(ifs);
    std::shared_ptr<Parser::Parser> parser = std::make_shared<Parser::Parser>(lexer);


    std::unique_ptr<Parser::AST::ExpressionNode> ast = parser->Parse();
    PrettyPrint(ast.get());

    diagnostic->AddMessage(Diagnostic::DiagnosticMessage(Diagnostic::DiagnosticSeverity::HINT, Diagnostic::ErrorCode::LEXER_ERROR, Text::FileRange({ 0,0 }, { 0,0 }), "Just for test"));
    std::cout << *diagnostic.get();
}