import proc_compiler as asm
file = open("program.txt","w")
asmb = asm.Assembler(file)


asmb.LoadAсс(10)
asmb.mov("acc","B")
asmb.LoadAсс(2)
asmb.div("B","acc")
asmb.LoadAсс(ord('0') + 0x0080)
asmb.sum("acc","B")
asmb.mov("acc","D")


file.close()