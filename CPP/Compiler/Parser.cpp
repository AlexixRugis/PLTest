#include "Parser.h"
#include <string>
#include <iostream>

namespace Parser {
    AST::ExpressionNode* Parser::Parser::ParseExpression()
    {
        return ParseBinaryExpression();
    }

    AST::ExpressionNode* Parser::ParseUnaryExpression()
    {
        if (MatchToken(Lexer::TokenType::LPAR))
        {
            SubmitToken();
            AST::ExpressionNode* node = ParseExpression();
            if (!MatchToken(Lexer::TokenType::RPAR)) ThrowError("Expected ')'");
            SubmitToken();
            return node;
        }

        return ParseConstExpression();
    }

    AST::ExpressionNode* Parser::ParseBinaryExpression(int leftPrecedence)
    {
        AST::ExpressionNode* cur = ParseUnaryExpression();

        while (MatchToken(Lexer::TokenType::PLUS) || MatchToken(Lexer::TokenType::MULT))
        {
            AST::NodeKind kind = AST::NodeKind::ADD;
            if (MatchToken(Lexer::TokenType::PLUS)) kind = AST::NodeKind::ADD;
            else if (MatchToken(Lexer::TokenType::MULT)) kind = AST::NodeKind::MULT;

            int rightPrecedence = GetBinaryOperatorPrecedence(kind);

            // <=left-to-right <right-to-left
            if (leftPrecedence != 0 && rightPrecedence <= leftPrecedence) break;


            SubmitToken();
            cur = new AST::BinaryExpressionNode(kind, cur, ParseBinaryExpression(rightPrecedence));
        }


        return cur;
    }

    AST::ExpressionNode* Parser::ParseConstExpression()
    {
        if (!MatchToken(Lexer::TokenType::NUM)) ThrowError("Expected NUM token");

        long long num = std::stoll(m_Current.Value());
        AST::ConstNode* node = new AST::ConstNode(AST::NodeKind::CONST, num);

        SubmitToken();
        return node;
    }

    int Parser::GetBinaryOperatorPrecedence(AST::NodeKind oper) const
    {
        if (oper == AST::NodeKind::MULT || oper == AST::NodeKind::DIV) return 2;
        else if (oper == AST::NodeKind::ADD || oper == AST::NodeKind::SUBTRACT) return 1;
        return 0;
    }

    void Parser::ThrowError(const std::string& error) const
    {
        std::cout << "Parsing error: " << error << std::endl;
        exit(-1);
    }
    void Parser::SubmitToken()
    {
        if (m_Current.Type() == Lexer::TokenType::ENDOFFILE) throw std::logic_error("Parser::SubmitToken : can't submit EOF token.");

        std::cout << Lexer::ToString(m_Current.Type()) << std::endl;
        m_Current = m_Lexer->NextToken();
    }
}