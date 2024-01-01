import sys
from PL.lexer.Lexer import Lexer
from .SyntaxNode import SyntaxNode

class Parser:

    '''syntax
    statement -> 'print' term |
        'if' paren_expr statement ('else' statement) |
        'while' paren_expr statement |
        '{' statement+ '}' |
        expr ';'
    paren_expr -> '(' expr ')'
    expr -> var '=' expr |
        test
    test -> summa ('<' summa)
    summa -> term ('*'|'/'|'+'|'-' summa)+
    term -> '-' term |
        '+' term |
        id |
        num |
        string |
        paren_expr
    '''

    VAR, CONST, STRING, ADD, SUB, MULT, DIV, LT, SET, PRINT, IF1, IF2, WHILE, EMPTY, SEQ, EXPR, UMINUS, PROG = range(18)

    def __init__(self, lexer):
        self.lexer = lexer
    
    def get_binary_operator_precedence(self, operator):
        if operator == Lexer.MULT or operator == Lexer.DIV:
            return 2
        elif operator == Lexer.PLUS or operator == Lexer.MINUS:
            return 1
        else:
            return 0

    def error(self, msg):
        print(f'Parser error at {(self.lexer.str_num, self.lexer.ch_num)}: {msg}')
        sys.exit(1)

    def term(self):
        '''term : id | num | string | paren_expr'''
        if self.lexer.sym == Lexer.MINUS:
            self.lexer.next_tok()
            n = SyntaxNode(Parser.UMINUS, op1=self.term())
            return n
        elif self.lexer.sym == Lexer.PLUS:
            self.lexer.next_tok()
            return self.term()
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

    def summa(self, parent_precedence = 0):
        '''summa : term | term +- sum'''
        n = self.term()
        
        while True:
            precedence = self.get_binary_operator_precedence(self.lexer.sym)
            
            #left-most <= right-most <
            if precedence == 0 or precedence <= parent_precedence:
                break
            
            kind = {
                Lexer.PLUS : Parser.ADD,
                Lexer.MINUS : Parser.SUB, 
                Lexer.MULT : Parser.MULT,
                Lexer.DIV : Parser.DIV
            }[self.lexer.sym]
            
            self.lexer.next_tok()
            n = SyntaxNode(kind, op1=n, op2=self.summa(precedence))

        return n

    def test(self):
        '''test : summa | summa < summa'''
        n = self.summa()
        if self.lexer.sym == Lexer.LESS:
            self.lexer.next_tok()
            n = SyntaxNode(Parser.LT, op1 = n, op2 = self.summa())
        return n

    def expr(self):
        '''expr : test | var = expr'''
        if self.lexer.sym != Lexer.ID:
            return self.test()
        n = self.test()
        if n.kind == Parser.VAR and self.lexer.sym == Lexer.EQUAL:
            self.lexer.next_tok()
            n = SyntaxNode(Parser.SET, op1 = n, op2 = self.expr())
        return n

    def paren_expr(self):
        '''paren_expr : (expr)'''
        if self.lexer.sym != Lexer.LPAR:
            self.error('"(" expected')
        self.lexer.next_tok()
        n = self.expr()
        if self.lexer.sym != Lexer.RPAR:
            self.error('")" expected')
        self.lexer.next_tok()
        return n

    def statement(self):
        '''statement : print paren_expr | if paren_expr statement | if paren_expr statement else statement | while paren_expr statement | semicolon | { statement+ } | expr+'''
        if self.lexer.sym == Lexer.PRINT:
            n = SyntaxNode(Parser.PRINT)
            self.lexer.next_tok()
            n.op1 = self.paren_expr()
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
