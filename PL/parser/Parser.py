import sys
from PL.lexer.Lexer import Lexer
from .SyntaxNode import SyntaxNode

class Parser:

    VAR, CONST, STRING, ADD, SUB, LT, SET, PRINT, IF1, IF2, WHILE, EMPTY, SEQ, EXPR, PROG = range(15)

    def __init__(self, lexer):
        self.lexer = lexer

    def error(self, msg):
        print('Parser error:', msg)
        sys.exit(1)

    def term(self):
        if self.lexer.sym == Lexer.ID:
            n = SyntaxNode(Parser.VAR, self.lexer.value)
            self.lexer.next_tok()
            return n
        elif self.lexer.sym == Lexer.NUM:
            n = SyntaxNode(Parser.CONST, self.lexer.value)
            self.lexer.next_tok()
            return n
        elif self.lexer.sym == Lexer.STRING:
            n = SyntaxNode(Parser.STRING, self.lexer.value)
            self.lexer.next_tok()
            return n
        else:
            return self.paren_expr()

    def summa(self):
        n = self.term()
        while self.lexer.sym == Lexer.PLUS or self.lexer.sym == Lexer.MINUS:
            if self.lexer.sym == Lexer.PLUS:
                kind = Parser.ADD
            else:
                kind = Parser.SUB
            self.lexer.next_tok()
            n = SyntaxNode(kind, op1 = n, op2 = self.term())
        return n

    def test(self):
        n = self.summa()
        if self.lexer.sym == Lexer.LESS:
            self.lexer.next_tok()
            n = SyntaxNode(Parser.LT, op1 = n, op2 = self.summa())
        return n

    def expr(self):
        if self.lexer.sym != Lexer.ID:
            return self.test()
        n = self.test()
        if n.kind == Parser.VAR and self.lexer.sym == Lexer.EQUAL:
            self.lexer.next_tok()
            n = SyntaxNode(Parser.SET, op1 = n, op2 = self.expr())
        return n

    def paren_expr(self):
        if self.lexer.sym != Lexer.LPAR:
            self.error('"(" expected')
        self.lexer.next_tok()
        n = self.expr()
        if self.lexer.sym != Lexer.RPAR:
            self.error('")" expected')
        self.lexer.next_tok()
        return n

    def statement(self):
        if self.lexer.sym == Lexer.PRINT:
            n = SyntaxNode(Parser.PRINT)
            self.lexer.next_tok()
            n.op1 = self.term()
        elif self.lexer.sym == Lexer.IF:
            n = SyntaxNode(Parser.IF1)
            self.lexer.next_tok()
            n.op1 = self.paren_expr()
            n.op2 = self.statement()
            if self.lexer.sym == Lexer.ELSE:
                n.kind = Parser.IF2
                self.lexer.next_tok()
                n.op3 = self.statement()
        elif self.lexer.sym == Lexer.WHILE:
            n = SyntaxNode(Parser.WHILE)
            self.lexer.next_tok()
            n.op1 = self.paren_expr()
            n.op2 = self.statement()
        elif self.lexer.sym == Lexer.SEMICOLON:
            n = SyntaxNode(Parser.EMPTY)
            self.lexer.next_tok()
        elif self.lexer.sym == Lexer.LBRA:
            n = SyntaxNode(Parser.EMPTY)
            self.lexer.next_tok()
            while self.lexer.sym != Lexer.RBRA:
                n = SyntaxNode(Parser.SEQ, op1 = n, op2 = self.statement())
            self.lexer.next_tok()
        else:
            n = SyntaxNode(Parser.EXPR, op1 = self.expr())
            if self.lexer.sym != Lexer.SEMICOLON:
                self.error('";" expected')
            self.lexer.next_tok()
        return n

    def parse(self):
        self.lexer.next_tok()
        node = SyntaxNode(Parser.PROG, op1 = self.statement())
        if (self.lexer.sym != Lexer.EOF):
            self.error("Invalid statement syntax")
        return node