#pragma once
#include <memory>
#include <stdexcept>
#include <optional>
#include "Lexer/Lexer.h"
#include "Lexer/LexerToken.h"
#include "Parser/ExpressionNode.h"
#include "Parser/UnaryExpressionNode.h"
#include "Parser/BinaryExpressionNode.h"
#include "Parser/ConstNode.h"
#include "Parser/BinaryOperatorInfo.h"

namespace Parser {
    class Parser final
    {
    public:
        Parser(const std::shared_ptr<Lexer::Lexer>& lexer) : m_Lexer(lexer), m_Current(lexer->NextToken()) {}

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

        std::optional<AST::NodeKind> GetNodeKind(Lexer::TokenType tokenType) const;
        std::optional<AST::BinaryOperatorInfo> GetOperatorInfo(AST::NodeKind kind) const;

        AST::ExpressionNode* ParseUnaryExpression();
        AST::ExpressionNode* ParseBinaryExpression(int leftPrecedence = 0);
        AST::ExpressionNode* ParseConstExpression();
    };
}