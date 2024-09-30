#pragma once
#include <memory>
#include <stdexcept>
#include "Lexer.h"
#include "LexerToken.h"
#include "ExpressionNode.h"
#include "UnaryExpressionNode.h"
#include "BinaryExpressionNode.h"
#include "ConstNode.h"

namespace Parser {
    class Parser final
    {
    public:
        Parser(const std::shared_ptr<Lexer::Lexer>& lexer) : m_Lexer(lexer), m_Current(lexer->NextToken()) { }

        AST::ExpressionNode* ParseExpression();

    private:
        std::shared_ptr<Lexer::Lexer> m_Lexer;
        Lexer::Token m_Current;

        int GetBinaryOperatorPrecedence(AST::NodeKind oper) const;

        void ThrowError(const std::string& error) const;

        bool MatchToken(Lexer::TokenType type) const
        {
            return m_Current.Type() == type;
        }

        void SubmitToken();

        AST::ExpressionNode* ParseUnaryExpression();
        AST::ExpressionNode* ParseBinaryExpression(int leftPrecedence = 0);
        AST::ExpressionNode* ParseConstExpression();
    };
}