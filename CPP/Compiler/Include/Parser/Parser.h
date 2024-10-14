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

        std::unique_ptr<AST::ExpressionNode> Parse();
    private:
        std::shared_ptr<Lexer::Lexer> m_Lexer;
        Lexer::Token m_Current;

        int GetBinaryOperatorPrecedence(AST::Op oper) const;

        void ThrowError(const std::string& error) const;

        bool Match(Lexer::TokenType type) const
        {
            return m_Current.Type() == type;
        }

        void Expect(Lexer::TokenType type)
        {
            if (m_Current.Type() != type) ThrowError("Expected " + Lexer::ToString(type) + " token.");
            SubmitToken();
        }

        void SubmitToken();

        std::optional<AST::Op> GetNodeKind(Lexer::TokenType tokenType) const;
        std::optional<AST::BinaryOperatorInfo> GetOperatorInfo(AST::Op kind) const;
        
        std::unique_ptr<AST::ExpressionNode> ParseStatement();
        std::unique_ptr<AST::ExpressionNode> ParseBlock();
        std::unique_ptr<AST::ExpressionNode> ParseExpression();
        std::unique_ptr<AST::ExpressionNode> ParseUnaryExpression();
        std::unique_ptr<AST::ExpressionNode> ParseBinaryExpression(int leftPrecedence = 0);
        std::unique_ptr<AST::ExpressionNode> ParseConstExpression();
        
    };
}