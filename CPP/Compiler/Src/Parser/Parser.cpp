#include <string>
#include <iostream>
#include <unordered_map>
#include "Parser/Parser.h"
#include "Parser/VariableNode.h"

namespace Parser {

    static const std::unordered_map<Lexer::TokenType, AST::NodeKind> nodeKindMap = {
        { Lexer::TokenType::PLUS, AST::NodeKind::ADD },
        { Lexer::TokenType::MINUS, AST::NodeKind::SUBTRACT },
        { Lexer::TokenType::MULT, AST::NodeKind::MULT },
        { Lexer::TokenType::DIV, AST::NodeKind::DIV },
        { Lexer::TokenType::REMAINDER, AST::NodeKind::REMAINDER },
        { Lexer::TokenType::SHIFTLEFT, AST::NodeKind::LSHIFT },
        { Lexer::TokenType::SHIFTRIGHT, AST::NodeKind::RSHIFT },
        { Lexer::TokenType::LESS, AST::NodeKind::LESS },
        { Lexer::TokenType::GREATER, AST::NodeKind::GREATER },
        { Lexer::TokenType::LESSEQUAL, AST::NodeKind::LESSEQUAL },
        { Lexer::TokenType::GREATEREQUAL, AST::NodeKind::GREATEREQUAL },
        { Lexer::TokenType::EQUAL, AST::NodeKind::EQUAL },
        { Lexer::TokenType::NOTEQUAL, AST::NodeKind::NOTEQUAL },
        { Lexer::TokenType::BITAND, AST::NodeKind::BITAND },
        { Lexer::TokenType::BITXOR, AST::NodeKind::BITXOR },
        { Lexer::TokenType::BITOR, AST::NodeKind::BITOR },
        { Lexer::TokenType::AND, AST::NodeKind::LOGICALAND },
        { Lexer::TokenType::OR, AST::NodeKind::LOGICALOR },
        { Lexer::TokenType::ASSIGN, AST::NodeKind::ASSIGN },
        { Lexer::TokenType::PLUSASSIGN, AST::NodeKind::PLUSASSIGN },
        { Lexer::TokenType::MINUSASSIGN, AST::NodeKind::MINUSASSIGN },
        { Lexer::TokenType::MULTASSIGN, AST::NodeKind::MULTASSIGN },
        { Lexer::TokenType::DIVASSIGN, AST::NodeKind::DIVASSIGN },
        { Lexer::TokenType::REMAINDERASSIGN, AST::NodeKind::REMASSIGN },
        { Lexer::TokenType::BITANDASSIGN, AST::NodeKind::ANDASSIGN },
        { Lexer::TokenType::BITORASSIGN, AST::NodeKind::ORASSIGN },
        { Lexer::TokenType::BITXORASSIGN, AST::NodeKind::XORASSIGN },
        { Lexer::TokenType::LEFTSHIFTASSIGN, AST::NodeKind::LSHIFTASSIGN },
        { Lexer::TokenType::RIGHTSHIFTASSIGN, AST::NodeKind::RSHIFTASSIGN },

    };

    static const std::unordered_map<AST::NodeKind, AST::BinaryOperatorInfo> operatorInfoMap = {
        // --------------
        { AST::NodeKind::MULT, AST::BinaryOperatorInfo(100, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::NodeKind::DIV, AST::BinaryOperatorInfo(100, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::NodeKind::REMAINDER, AST::BinaryOperatorInfo(100, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::ADD, AST::BinaryOperatorInfo(99, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::NodeKind::SUBTRACT, AST::BinaryOperatorInfo(99, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::LSHIFT, AST::BinaryOperatorInfo(98, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::NodeKind::RSHIFT, AST::BinaryOperatorInfo(98, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::LESS, AST::BinaryOperatorInfo(97, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::NodeKind::LESSEQUAL, AST::BinaryOperatorInfo(97, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::NodeKind::GREATER, AST::BinaryOperatorInfo(97, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::NodeKind::GREATEREQUAL, AST::BinaryOperatorInfo(97, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::EQUAL, AST::BinaryOperatorInfo(96, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::NodeKind::NOTEQUAL, AST::BinaryOperatorInfo(96, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::BITAND, AST::BinaryOperatorInfo(95, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::BITXOR, AST::BinaryOperatorInfo(94, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::BITOR, AST::BinaryOperatorInfo(93, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::LOGICALAND, AST::BinaryOperatorInfo(92, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::LOGICALOR, AST::BinaryOperatorInfo(91, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::NodeKind::ASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::PLUSASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::MINUSASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::MULTASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::DIVASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::REMASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::ANDASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::ORASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::XORASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::LSHIFTASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::NodeKind::RSHIFTASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
    };

    std::optional<AST::NodeKind> Parser::GetNodeKind(Lexer::TokenType tokenType) const
    {
        auto iter = nodeKindMap.find(tokenType);
        if (iter != nodeKindMap.end())
        {
            return iter->second;
        }

        return std::nullopt;
    }

    std::optional<AST::BinaryOperatorInfo> Parser::GetOperatorInfo(AST::NodeKind kind) const
    {
        auto iter = operatorInfoMap.find(kind);
        if (iter != operatorInfoMap.end())
        {
            return iter->second;
        }

        return std::nullopt;
    }

    AST::ExpressionNode* Parser::ParseExpression()
    {
        return ParseBinaryExpression();
    }

    AST::ExpressionNode* Parser::ParseUnaryExpression()
    {
        if (MatchToken(Lexer::TokenType::MINUS))
        {
            SubmitToken();
            return new AST::UnaryExpressionNode(AST::NodeKind::UNARYMINUS, ParseUnaryExpression());
        }

        if (MatchToken(Lexer::TokenType::PLUS))
        {
            SubmitToken();
            return ParseUnaryExpression();
        }

        if (MatchToken(Lexer::TokenType::LPAR))
        {
            SubmitToken();
            AST::ExpressionNode* node = ParseExpression();
            if (!MatchToken(Lexer::TokenType::RPAR)) ThrowError("Expected ')'");
            SubmitToken();
            return node;
        }

        if (MatchToken(Lexer::TokenType::ID))
        {
            AST::VariableNode* node = new AST::VariableNode(AST::NodeKind::VARIABLE, m_Current.Value());
            SubmitToken();
            return node;
            
        }

        return ParseConstExpression();
    }

    AST::ExpressionNode* Parser::ParseBinaryExpression(int leftPrecedence)
    {
        AST::ExpressionNode* cur = ParseUnaryExpression();

        while (true)
        {
            std::optional<AST::NodeKind> kind = GetNodeKind(m_Current.Type());
            if (!kind.has_value())
            {
                break;
            }

            std::optional<AST::BinaryOperatorInfo> operatorInfo = GetOperatorInfo(kind.value());

            if (!operatorInfo.has_value())
            {
                ThrowError("Binary operator expected");
            }

            int rightPrecedence = operatorInfo.value().Precedence();

            // <=left-to-right <right-to-left
            if (leftPrecedence != 0 && rightPrecedence <= leftPrecedence) break;


            SubmitToken();
            cur = new AST::BinaryExpressionNode(kind.value(), cur, ParseBinaryExpression(rightPrecedence));
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
        if (m_Current.Type() == Lexer::TokenType::ENDOFFILE) throw std::logic_error(__FUNCTION__ " : can't submit EOF token.");

        m_Current = m_Lexer->NextToken();
    }
}