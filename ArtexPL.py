import sys



class Assembler(object):
    def __init__(self, input):
        self.file = input

    def ChooseReg(self,aa):
        if str(aa) == 'acc':
            return 1
        elif str(aa) == 'pc':
            return 8
        elif str(aa) == 'adr':
            return 2
        elif str(aa) == 'A':
            return 3
        elif str(aa) == 'B':
            return 4
        elif str(aa) == 'C':
            return 5
        elif str(aa) == 'D':
            return 6
        elif str(aa) == 'Ram':
            return 7
        else:
            print('choose reg a error!')
            self.file.close()
            sys.exit(0)

    def LoadAcc(self, a):
        global pc
        if a >= 0 and a <= 32767:
            self.file.append('loadacc ')
            self.file.append(str(a) + ' ')
            pc += 2
        else:
            print("число выходит за границы допустимого диапазона!")


    def mov(self,a,b):
        global pc
        self.file.append('mov ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def sum(self,a,b):
        global pc
        self.file.append('sum ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def sub(self,a,b):
        global pc
        self.file.append('sub ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def mult(self,a,b):
        global pc
        self.file.append('mult ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def div(self,a,b):
        global pc
        self.file.append('div ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def shl(self,a,b):
        global pc
        self.file.append('shl ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def shr(self,a,b):
        global pc
        self.file.append('shr ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def And(self,a,b):
        global pc
        self.file.append('and ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def inv(self,a):
        global pc
        self.file.append('inv ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        pc += 2

    def inc(self,a):
        global pc
        self.file.append('inc ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        pc += 2

    def dec(self,a):
        global pc
        self.file.append('dec ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        pc += 2

    def mod(self, a, b):
        global pc
        self.file.append('mod ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def ilt(self, a, b):
        global pc
        self.file.append('ilt ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def jma(self):
        global pc
        self.file.append('jma ')
        pc += 1

    def jme(self,a,b):
        global pc
        self.file.append('jme ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def jml(self,a,b):
        global pc
        self.file.append('jml ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def jmg(self,a,b):
        global pc
        self.file.append('jmg ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def jmle(self,a,b):
        global pc
        self.file.append('jmle ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def jmge(self,a,b):
        global pc
        self.file.append('jmge ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def jmne(self,a,b):
        global pc
        self.file.append('jmne ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        pc += 3

    def push(self, num):
        self.LoadAcc(num)

    def store(self, adr):
        self.mov("acc", "A")
        self.LoadAcc(adr)
        self.mov("acc", "adr")
        self.mov("A", "Ram")

    def Load(self, adr):
        self.mov("acc", "A")
        self.LoadAcc(adr)
        self.mov("acc", "adr")
        self.mov("Ram", "acc")

    def Stop(self):
        global pc
        self.file.append('EOP ')
        pc += 1

    def print(self, opt, ch):
        global pc
        self.file.append('print ')
        self.file.append(opt + ' ')
        self.file.append(str(ch) + ' ')
        pc += 3

class Lexer:
    NUM, ID, STRING, PRINT, IF, ELSE, WHILE, LBRA, RBRA, LPAR, RPAR, PLUS, MINUS, LESS, \
    EQUAL, SEMICOLON, EOF = range(17)

    # специальные символы языка
    SYMBOLS = {'{': LBRA, '}': RBRA, '=': EQUAL, ';': SEMICOLON, '(': LPAR,
               ')': RPAR, '+': PLUS, '-': MINUS, '<': LESS}

    # ключевые слова
    WORDS = {'print': PRINT, 'if': IF, 'else': ELSE, 'while': WHILE}


    def __init__(self, file):
        self.file = file

    # текущий символ, считанный из исходника
    ch = ' '  # допустим, первый символ - это пробел

    def error(self, msg):
        print('Lexer error: ', msg)
        sys.exit(1)

    def getc(self):
        self.ch = self.file.read(1)

    def next_tok(self):
        self.value = None
        self.sym = None
        while self.sym == None:
            if len(self.ch) == 0:
                self.sym = lexer.EOF
            elif self.ch.isspace():
                self.getc()
            elif self.ch in Lexer.SYMBOLS:
                self.sym = Lexer.SYMBOLS[self.ch]
                self.getc()
            elif self.ch == '#':
                self.str = ''
                self.getc()
                while True:
                    if self.ch == "#":
                        break
                    self.str += self.ch
                    self.getc()
                self.sym = Lexer.STRING
                self.value = self.str
                self.getc()
            elif self.ch.isdigit():
                intval = 0
                while self.ch.isdigit():
                    intval = intval * 10 + int(self.ch)
                    self.getc()
                self.value = intval
                self.sym = Lexer.NUM
            elif self.ch.isalpha():
                ident = ''
                while self.ch.isalpha():
                    ident = ident + self.ch.lower()
                    self.getc()
                if ident in Lexer.WORDS:
                    self.sym = Lexer.WORDS[ident]
                else:
                    self.sym = Lexer.ID
                    self.value = ident
            else:
                self.error('Unexpected symbol: ' + self.ch)
        return [self.sym, self.value]

class Node:
    def __init__(self, kind, value = None, op1 = None, op2 = None, op3 = None):
        self.kind = kind
        self.value = value
        self.op1 = op1
        self.op2 = op2
        self.op3 = op3

class Parser:

    VAR, CONST, STRING, ADD, SUB, LT, SET, PRINT, IF1, IF2, WHILE, EMPTY, SEQ, EXPR, PROG = range(15)

    def __init__(self, lexer):
        self.lexer = lexer

    def error(self, msg):
        print('Parser error:', msg)
        sys.exit(1)

    def term(self):
        if self.lexer.sym == Lexer.ID:
            n = Node(Parser.VAR, self.lexer.value)
            self.lexer.next_tok()
            return n
        elif self.lexer.sym == Lexer.NUM:
            n = Node(Parser.CONST, self.lexer.value)
            self.lexer.next_tok()
            return n
        elif self.lexer.sym == Lexer.STRING:
            n = Node(Parser.STRING, self.lexer.value)
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
            n = Node(kind, op1 = n, op2 = self.term())
        return n

    def test(self):
        n = self.summa()
        if self.lexer.sym == Lexer.LESS:
            self.lexer.next_tok()
            n = Node(Parser.LT, op1 = n, op2 = self.summa())
        return n

    def expr(self):
        if self.lexer.sym != Lexer.ID:
            return self.test()
        n = self.test()
        if n.kind == Parser.VAR and self.lexer.sym == Lexer.EQUAL:
            self.lexer.next_tok()
            n = Node(Parser.SET, op1 = n, op2 = self.expr())
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
            n = Node(Parser.PRINT)
            self.lexer.next_tok()
            n.op1 = self.term()
        elif self.lexer.sym == Lexer.IF:
            n = Node(Parser.IF1)
            self.lexer.next_tok()
            n.op1 = self.paren_expr()
            n.op2 = self.statement()
            if self.lexer.sym == Lexer.ELSE:
                n.kind = Parser.IF2
                self.lexer.next_tok()
                n.op3 = self.statement()
        elif self.lexer.sym == Lexer.WHILE:
            n = Node(Parser.WHILE)
            self.lexer.next_tok()
            n.op1 = self.paren_expr()
            n.op2 = self.statement()
        elif self.lexer.sym == Lexer.SEMICOLON:
            n = Node(Parser.EMPTY)
            self.lexer.next_tok()
        elif self.lexer.sym == Lexer.LBRA:
            n = Node(Parser.EMPTY)
            self.lexer.next_tok()
            while self.lexer.sym != Lexer.RBRA:
                n = Node(Parser.SEQ, op1 = n, op2 = self.statement())
            self.lexer.next_tok()
        else:
            n = Node(Parser.EXPR, op1 = self.expr())
            if self.lexer.sym != Lexer.SEMICOLON:
                self.error('";" expected')
            self.lexer.next_tok()
        return n

    def parse(self):
        self.lexer.next_tok()
        node = Node(Parser.PROG, op1 = self.statement())
        if (self.lexer.sym != Lexer.EOF):
            self.error("Invalid statement syntax")
        return node


class Compiler:
    program = []
    variables = {}
    free_mem_addr = 0

    def __init__(self, asmb):
        self.asmb = asmb

    def gen(self, command):
        self.program.append(command)

    def compile(self, node):
        global pc
        if node.kind == Parser.VAR:
            self.asmb.Load(self.variables[node.value])
        elif node.kind == Parser.CONST:
            self.asmb.push(node.value)
        elif node.kind == Parser.ADD:
            self.compile(node.op1)
            self.asmb.mov("acc","A")
            self.compile(node.op2)
            self.asmb.mov("acc", "B")
            self.asmb.sum("A","B")
            self.asmb.mov("A","acc")
        elif node.kind == Parser.SUB:
            self.compile(node.op1)
            self.asmb.mov("acc", "A")
            self.compile(node.op2)
            self.asmb.mov("acc", "B")
            self.asmb.sub("A", "B")
            self.asmb.mov("A", "acc")
        elif node.kind == Parser.LT:
            self.compile(node.op1)
            self.asmb.mov("acc", "A")
            self.compile(node.op2)
            self.asmb.mov("acc", "B")
            self.asmb.ilt("A","B")
            self.asmb.mov("A", "acc")

        elif node.kind == Parser.SET:
            self.compile(node.op2)
            if node.op1.value not in self.variables:
                self.variables[node.op1.value] = self.free_mem_addr
                self.free_mem_addr += 1
            asmb.store(self.variables[node.op1.value])

        elif node.kind == Parser.PRINT:
            if node.op1.kind == Parser.STRING:
                for ch in node.op1.value:
                    self.asmb.print('char', ord(ch))
            elif node.op1.kind == Parser.VAR:
                self.compile(node.op1)
                self.asmb.print('reg', 1)

        elif node.kind == Parser.IF1:
            self.compile(node.op1)
            self.asmb.mov("acc", "A")
            self.asmb.LoadAcc(0)
            self.asmb.mov("acc", "B")
            addr = pc
            self.asmb.LoadAcc(0)

            self.asmb.mov("acc", "adr")
            self.asmb.jme("A","B")
            self.compile(node.op2)
            self.asmb.file[addr + 1] = str(pc) + ' '

        elif node.kind == Parser.IF2:
            self.compile(node.op1)
            self.asmb.mov("acc", "A")
            self.asmb.LoadAcc(0)
            self.asmb.mov("acc", "B")
            addr1 = pc
            self.asmb.LoadAcc(0)

            self.asmb.mov("acc", "adr")
            self.asmb.jme("A", "B")

            self.compile(node.op2)
            addr2 = pc
            self.asmb.LoadAcc(0)
            self.asmb.mov("acc", "adr")
            self.asmb.jma()

            print(addr2)
            self.asmb.file[addr1 + 1] = str(pc) + ' '
            self.compile(node.op3)
            self.asmb.file[addr2 + 1] = str(pc) + ' '

        elif node.kind == Parser.WHILE:
            addr1 = pc
            self.compile(node.op1)
            self.asmb.mov("acc","A")
            self.asmb.LoadAcc(0)
            self.asmb.mov("acc","B")
            addr2 = pc
            self.asmb.LoadAcc(0)
            self.asmb.mov("acc", "adr")
            self.asmb.jme("A","B")

            self.compile(node.op2)

            self.asmb.LoadAcc(addr1)
            self.asmb.mov("acc", "adr")
            self.asmb.jma()
            self.asmb.file[addr2 + 1] = str(pc) + ' '
        elif node.kind == Parser.SEQ:
            self.compile(node.op1)
            self.compile(node.op2)
        elif node.kind == Parser.EXPR:
            self.compile(node.op1)
        elif node.kind == Parser.PROG:
            self.compile(node.op1)
            self.asmb.Stop()
            pc += 1


with open("input.txt", 'r') as file:
    lexer = Lexer(file)
    lexems = []
    parser = Parser(lexer)
    parsed = parser.parse()
    file.close()
pc = 0
program = []
asmb = Assembler(program)
compl = Compiler(asmb)
compl.compile(parsed)
print(program)
print(len(program))
with open("program.txt", 'w') as file:
    for com in program:
        file.write(com)
    file.close()
