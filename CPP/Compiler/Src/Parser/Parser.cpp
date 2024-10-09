#include <string>
#include <iostream>
#include <unordered_map>
#include "Parser/Parser.h"
#include "Parser/VariableNode.h"

namespace Parser {

    static const std::unordered_map<Lexer::TokenType, AST::Op> nodeKindMap = {
        { Lexer::TokenType::PLUS, AST::Op::ADD },
        { Lexer::TokenType::MINUS, AST::Op::SUBTRACT },
        { Lexer::TokenType::MULT, AST::Op::MULT },
        { Lexer::TokenType::DIV, AST::Op::DIV },
        { Lexer::TokenType::REMAINDER, AST::Op::REMAINDER },
        { Lexer::TokenType::SHIFTLEFT, AST::Op::LSHIFT },
        { Lexer::TokenType::SHIFTRIGHT, AST::Op::RSHIFT },
        { Lexer::TokenType::LESS, AST::Op::LESS },
        { Lexer::TokenType::GREATER, AST::Op::GREATER },
        { Lexer::TokenType::LESSEQUAL, AST::Op::LESSEQUAL },
        { Lexer::TokenType::GREATEREQUAL, AST::Op::GREATEREQUAL },
        { Lexer::TokenType::EQUAL, AST::Op::EQUAL },
        { Lexer::TokenType::NOTEQUAL, AST::Op::NOTEQUAL },
        { Lexer::TokenType::BITAND, AST::Op::BITAND },
        { Lexer::TokenType::BITXOR, AST::Op::BITXOR },
        { Lexer::TokenType::BITOR, AST::Op::BITOR },
        { Lexer::TokenType::AND, AST::Op::LOGICALAND },
        { Lexer::TokenType::OR, AST::Op::LOGICALOR },
        { Lexer::TokenType::ASSIGN, AST::Op::ASSIGN },
        { Lexer::TokenType::PLUSASSIGN, AST::Op::PLUSASSIGN },
        { Lexer::TokenType::MINUSASSIGN, AST::Op::MINUSASSIGN },
        { Lexer::TokenType::MULTASSIGN, AST::Op::MULTASSIGN },
        { Lexer::TokenType::DIVASSIGN, AST::Op::DIVASSIGN },
        { Lexer::TokenType::REMAINDERASSIGN, AST::Op::REMASSIGN },
        { Lexer::TokenType::BITANDASSIGN, AST::Op::ANDASSIGN },
        { Lexer::TokenType::BITORASSIGN, AST::Op::ORASSIGN },
        { Lexer::TokenType::BITXORASSIGN, AST::Op::XORASSIGN },
        { Lexer::TokenType::LEFTSHIFTASSIGN, AST::Op::LSHIFTASSIGN },
        { Lexer::TokenType::RIGHTSHIFTASSIGN, AST::Op::RSHIFTASSIGN },

    };

    static const std::unordered_map<AST::Op, AST::BinaryOperatorInfo> operatorInfoMap = {
        // --------------
        { AST::Op::MULT, AST::BinaryOperatorInfo(100, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::Op::DIV, AST::BinaryOperatorInfo(100, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::Op::REMAINDER, AST::BinaryOperatorInfo(100, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::ADD, AST::BinaryOperatorInfo(99, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::Op::SUBTRACT, AST::BinaryOperatorInfo(99, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::LSHIFT, AST::BinaryOperatorInfo(98, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::Op::RSHIFT, AST::BinaryOperatorInfo(98, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::LESS, AST::BinaryOperatorInfo(97, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::Op::LESSEQUAL, AST::BinaryOperatorInfo(97, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::Op::GREATER, AST::BinaryOperatorInfo(97, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::Op::GREATEREQUAL, AST::BinaryOperatorInfo(97, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::EQUAL, AST::BinaryOperatorInfo(96, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        { AST::Op::NOTEQUAL, AST::BinaryOperatorInfo(96, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::BITAND, AST::BinaryOperatorInfo(95, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::BITXOR, AST::BinaryOperatorInfo(94, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::BITOR, AST::BinaryOperatorInfo(93, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::LOGICALAND, AST::BinaryOperatorInfo(92, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::LOGICALOR, AST::BinaryOperatorInfo(91, AST::BinaryOperatorAssociativity::LEFTTORIGHT) },
        // --------------
        { AST::Op::ASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::PLUSASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::MINUSASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::MULTASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::DIVASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::REMASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::ANDASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::ORASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::XORASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::LSHIFTASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
        { AST::Op::RSHIFTASSIGN, AST::BinaryOperatorInfo(90, AST::BinaryOperatorAssociativity::RIGHTTOLEFT) },
    };

    std::optional<AST::Op> Parser::GetNodeKind(Lexer::TokenType tokenType) const
    {
        auto iter = nodeKindMap.find(tokenType);
        if (iter != nodeKindMap.end())
        {
            return iter->second;
        }

        return std::nullopt;
    }

    std::optional<AST::BinaryOperatorInfo> Parser::GetOperatorInfo(AST::Op kind) const
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
            return new AST::UnaryExpressionNode(AST::Op::UNARYMINUS, ParseUnaryExpression());
        }

        if (MatchToken(Lexer::TokenType::INCREMENT))
        {
            SubmitToken();
            return new AST::UnaryExpressionNode(AST::Op::PREINC, ParseUnaryExpression());
        }

        if (MatchToken(Lexer::TokenType::DECREMENT))
        {
            SubmitToken();
            return new AST::UnaryExpressionNode(AST::Op::PREDEC, ParseUnaryExpression());
        }

        if (MatchToken(Lexer::TokenType::NOT))
        {
            SubmitToken();
            return new AST::UnaryExpressionNode(AST::Op::NOT, ParseUnaryExpression());
        }

        if (MatchToken(Lexer::TokenType::BITNOT))
        {
            SubmitToken();
            return new AST::UnaryExpressionNode(AST::Op::BITNOT, ParseUnaryExpression());
        }

        if (MatchToken(Lexer::TokenType::PLUS))
        {
            SubmitToken();
            return ParseUnaryExpression();
        }

        AST::ExpressionNode* node;
        if (MatchToken(Lexer::TokenType::LPAR))
        {
            SubmitToken();
            node = ParseExpression();
            if (!MatchToken(Lexer::TokenType::RPAR)) ThrowError("Expected ')'");
            SubmitToken();
        } else if (MatchToken(Lexer::TokenType::ID))
        {
            node = new AST::VariableNode(AST::Op::ID, m_Current.Value());
            SubmitToken();
        } else
        {
            node = ParseConstExpression();
        }

        while (true)
        {
            if (MatchToken(Lexer::TokenType::INCREMENT))
            {
                node = new AST::UnaryExpressionNode(AST::Op::POSTINC, node);
                SubmitToken();
            } else if (MatchToken(Lexer::TokenType::DECREMENT))
            {
                node = new AST::UnaryExpressionNode(AST::Op::POSTDEC, node);
                SubmitToken();
            } else if (MatchToken(Lexer::TokenType::LIND))
            {
                SubmitToken();
                node = new AST::BinaryExpressionNode(AST::Op::INDEX, node, ParseExpression());
                if (!MatchToken(Lexer::TokenType::RIND)) ThrowError("Expected ']'");
                SubmitToken();
            } else if (MatchToken(Lexer::TokenType::DOT))
            {
                SubmitToken();
                if (!MatchToken(Lexer::TokenType::ID)) ThrowError("Expected ID");
                node = new AST::BinaryExpressionNode(AST::Op::MEMBER, node, new AST::VariableNode(AST::Op::ID, m_Current.Value()));
                SubmitToken();
            } else if (MatchToken(Lexer::TokenType::LPAR))
            {
                SubmitToken();
                if (!MatchToken(Lexer::TokenType::RPAR)) ThrowError("Expected ')'");
                SubmitToken();
                node = new AST::UnaryExpressionNode(AST::Op::CALL, node);
            }
            else
            {
                break;
            }
        }

        return node;
    }

    AST::ExpressionNode* Parser::ParseBinaryExpression(int leftPrecedence)
    {
        AST::ExpressionNode* cur = ParseUnaryExpression();

        while (true)
        {
            std::optional<AST::Op> kind = GetNodeKind(m_Current.Type());
            if (!kind.has_value())
            {
                break;
            }

            std::optional<AST::BinaryOperatorInfo> operatorInfo = GetOperatorInfo(kind.value());

            if (!operatorInfo.has_value())
            {
                ThrowError("Binary operator expected");
            }

            AST::BinaryOperatorAssociativity asc = operatorInfo.value().Associativity();
            int rightPrecedence = operatorInfo.value().Precedence();

            // <=left-to-right < right-to-left
            if (asc == AST::BinaryOperatorAssociativity::RIGHTTOLEFT)
            {
                if (leftPrecedence != 0 && rightPrecedence < leftPrecedence) break;
            }
            else
            {
                if (leftPrecedence != 0 && rightPrecedence <= leftPrecedence) break;
            }



            SubmitToken();
            cur = new AST::BinaryExpressionNode(kind.value(), cur, ParseBinaryExpression(rightPrecedence));
        }


        return cur;
    }

    AST::ExpressionNode* Parser::ParseConstExpression()
    {
        if (!MatchToken(Lexer::TokenType::NUM)) ThrowError("Expected NUM token");

        long long num = std::stoll(m_Current.Value());
        AST::ConstNode* node = new AST::ConstNode(AST::Op::CONST, num);

        SubmitToken();
        return node;
    }

    int Parser::GetBinaryOperatorPrecedence(AST::Op oper) const
    {
        if (oper == AST::Op::MULT || oper == AST::Op::DIV) return 2;
        else if (oper == AST::Op::ADD || oper == AST::Op::SUBTRACT) return 1;
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