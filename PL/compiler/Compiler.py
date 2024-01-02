import sys
from PL.parser.Parser import Parser

class Compiler:
    program = []
    variables = {}
    free_mem_addr = 0

    def __init__(self, asmb):
        self.asmb = asmb

    def gen(self, command):
        self.program.append(command)

    def compile(self, node):
        if node.kind == Parser.VAR:
            self.asmb.load(self.variables[node.value])
        elif node.kind == Parser.CONST:
            self.asmb.push(node.value)
        elif node.kind == Parser.UMINUS:
            self.compile(node.op1)
            self.asmb.push(0)
            self.asmb.sub()
        elif node.kind == Parser.ADD:
            self.compile(node.op2)
            self.compile(node.op1)
            self.asmb.sum()
        elif node.kind == Parser.SUB:
            self.compile(node.op2)
            self.compile(node.op1)
            self.asmb.sub()
        elif node.kind == Parser.MULT:
            self.compile(node.op2)
            self.compile(node.op1)
            self.asmb.mult()
        elif node.kind == Parser.DIV:
            self.compile(node.op2)
            self.compile(node.op1)
            self.asmb.div()
        elif node.kind == Parser.LT:
            self.compile(node.op2)
            self.compile(node.op1)
            self.asmb.ilt()

        elif node.kind == Parser.SET:
            self.compile(node.op2)
            if node.op1.value not in self.variables:
                self.variables[node.op1.value] = self.free_mem_addr
                self.free_mem_addr += 1
            self.asmb.store(self.variables[node.op1.value])

        elif node.kind == Parser.PRINT:
            if node.op1.kind == Parser.STRING:
                for ch in node.op1.value:
                    self.asmb.push(ord(ch))
                    self.asmb.printch()
            else:
                self.compile(node.op1)
                self.asmb.printnum()

        elif node.kind == Parser.IF1:
            self.compile(node.op1)
            self.asmb.push(0)
            addr = self.asmb.pc
            self.asmb.push(0)
            self.asmb.jme()
            self.compile(node.op2)
            self.asmb.file[addr + 1] = str(self.asmb.pc) + ' '

        elif node.kind == Parser.IF2:
            self.compile(node.op1)
            self.asmb.push(0)
            addr1 = self.asmb.pc
            self.asmb.push(0)
            self.asmb.jme()
            
            self.compile(node.op2)
            addr2 = self.asmb.pc
            self.asmb.push(0)
            self.asmb.jma()
            
            self.asmb.file[addr1 + 1] = str(self.asmb.pc) + ' '
            self.compile(node.op3)
            self.asmb.file[addr2 + 1] = str(self.asmb.pc) + ' '

        elif node.kind == Parser.WHILE:
            addr1 = self.asmb.pc
            self.compile(node.op1)
            self.asmb.push(0)
            addr2 = self.asmb.pc
            self.asmb.push(0)
            self.asmb.jme()
            
            self.compile(node.op2)
            self.asmb.push(addr1)
            self.asmb.jma()
            self.asmb.file[addr2 + 1] = str(self.asmb.pc) + ' '

        elif node.kind == Parser.SEQ:
            self.compile(node.op1)
            self.compile(node.op2)
        elif node.kind == Parser.EXPR:
            self.compile(node.op1)
        elif node.kind == Parser.PROG:
            self.compile(node.op1)
            self.asmb.eop()
            self.asmb.pc += 1
        elif node.kind == Parser.EMPTY:
            pass
        else:
            print(f'Unexpected syntax: {node}')
            sys.exit(-1)