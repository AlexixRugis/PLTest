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
            self.asmb.store(self.variables[node.op1.value])

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
            addr = self.asmb.pc
            self.asmb.LoadAcc(0)

            self.asmb.mov("acc", "adr")
            self.asmb.jme("A","B")
            self.compile(node.op2)
            self.asmb.file[addr + 1] = str(self.asmb.pc) + ' '

        elif node.kind == Parser.IF2:
            self.compile(node.op1)
            self.asmb.mov("acc", "A")
            self.asmb.LoadAcc(0)
            self.asmb.mov("acc", "B")
            addr1 = self.asmb.pc
            self.asmb.LoadAcc(0)

            self.asmb.mov("acc", "adr")
            self.asmb.jme("A", "B")

            self.compile(node.op2)
            addr2 = self.asmb.pc
            self.asmb.LoadAcc(0)
            self.asmb.mov("acc", "adr")
            self.asmb.jma()

            print(addr2)
            self.asmb.file[addr1 + 1] = str(self.asmb.pc) + ' '
            self.compile(node.op3)
            self.asmb.file[addr2 + 1] = str(self.asmb.pc) + ' '

        elif node.kind == Parser.WHILE:
            addr1 = self.asmb.pc
            self.compile(node.op1)
            self.asmb.mov("acc","A")
            self.asmb.LoadAcc(0)
            self.asmb.mov("acc","B")
            addr2 = self.asmb.pc
            self.asmb.LoadAcc(0)
            self.asmb.mov("acc", "adr")
            self.asmb.jme("A","B")

            self.compile(node.op2)

            self.asmb.LoadAcc(addr1)
            self.asmb.mov("acc", "adr")
            self.asmb.jma()
            self.asmb.file[addr2 + 1] = str(self.asmb.pc) + ' '
        elif node.kind == Parser.SEQ:
            self.compile(node.op1)
            self.compile(node.op2)
        elif node.kind == Parser.EXPR:
            self.compile(node.op1)
        elif node.kind == Parser.PROG:
            self.compile(node.op1)
            self.asmb.Stop()
            self.asmb.pc += 1