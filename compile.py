from PL.assembler.Assembler import Assembler
from PL.lexer.Lexer import Lexer
from PL.parser.Parser import Parser
from PL.compiler.Compiler import Compiler


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
parsed.pretty_print()
compl.compile(parsed)
print(program)
print(len(program))
with open("program.txt", 'w') as file:
    for com in program:
        file.write(com)
    file.close()
