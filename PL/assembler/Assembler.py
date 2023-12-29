import sys

class Assembler(object):
    def __init__(self, input):
        self.pc = 0
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
        if a >= 0 and a <= 32767:
            self.file.append('loadacc ')
            self.file.append(str(a) + ' ')
            self.pc += 2
        else:
            print("число выходит за границы допустимого диапазона!")


    def mov(self,a,b):
        self.file.append('mov ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def sum(self,a,b):
        self.file.append('sum ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def sub(self,a,b):
        self.file.append('sub ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def mult(self,a,b):
        self.file.append('mult ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def div(self,a,b):
        self.file.append('div ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def shl(self,a,b):
        self.file.append('shl ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def shr(self,a,b):
        self.file.append('shr ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def And(self,a,b):
        self.file.append('and ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def inv(self,a):
        self.file.append('inv ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.pc += 2

    def inc(self,a):
        self.file.append('inc ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.pc += 2

    def dec(self,a):
        self.file.append('dec ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.pc += 2

    def mod(self, a, b):
        self.file.append('mod ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def ilt(self, a, b):
        self.file.append('ilt ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def jma(self):
        self.file.append('jma ')
        self.pc += 1

    def jme(self,a,b):
        self.file.append('jme ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def jml(self,a,b):
        self.file.append('jml ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def jmg(self,a,b):
        self.file.append('jmg ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def jmle(self,a,b):
        self.file.append('jmle ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def jmge(self,a,b):
        self.file.append('jmge ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

    def jmne(self,a,b):
        self.file.append('jmne ')
        self.file.append(str(self.ChooseReg(a)) + ' ')
        self.file.append(str(self.ChooseReg(b)) + ' ')
        self.pc += 3

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
        self.file.append('EOP ')
        self.pc += 1

    def print(self, opt, ch):
        self.file.append('print ')
        self.file.append(opt + ' ')
        self.file.append(str(ch) + ' ')
        self.pc += 3