#ассемблер для процессора
import sys
class Assembler(object):
    def __init__(self, input):
        self.file = input
    def LoadAсс(self, a):
        global pc
        if a >= 0 and a <= 32767:
            self.file.append(hex(a)[2::] + ' ')
            pc += 1
        else:
            print("число выходит за границы допустимого диапазона!")

    def ChooseReg(self,aa):
        if str(aa) == 'ser':
            return 1
        elif str(aa) == 'pcr':
            return 2
        elif str(aa) == 'acr':
            return 3
        elif str(aa) == 'sar':
            return 4
        elif str(aa) == 'dar':
            return 5
        elif str(aa) == 'ar':
            return 6
        elif str(aa) == 'br':
            return 7
        elif str(aa) == 'cr':
            return 8
        elif str(aa) == 'dr':
            return 9
        else:
            print('choose reg a error!')
            self.file.close()
            sys.exit(0)

    def mov(self,a,b):
        global pc
        self.file.append('8' + 'b' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def sum(self,a,b):
        global pc
        self.file.append('8' + '0' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def sub(self,a,b):
        global pc
        self.file.append('8' + '1' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def mult(self,a,b):
        global pc
        self.file.append('8' + '2' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def div(self,a,b):
        global pc
        self.file.append('8' + '3' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def shl(self,a,b):
        global pc
        self.file.append('8' + '6' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def shr(self,a,b):
        global pc
        self.file.append('8' + '7' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def And(self,a,b):
        global pc
        self.file.append('8' + '8' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def Or(self,a,b):
        global pc
        self.file.append('8' + '9' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def Xor(self,a,b):
        global pc
        self.file.append('8' + 'a' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def inv(self,a,b):
        global pc
        self.file.append('8' + '5' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def mod(self, a, b):
        global pc
        self.file.append('8' + '4' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def jma(self, a):
        global pc
        self.file.append('f' + '0' + '0' + '0' + ' ')
        pc += 1

    def jme(self,a,b):
        global pc
        self.file.append('a' + '0' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def jml(self,a,b):
        global pc
        self.file.append('9' + '0' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def jmg(self,a,b):
        global pc
        self.file.append('c' + '0' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def jmle(self,a,b):
        global pc
        self.file.append('b' + '0' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def jmge(self,a,b):
        global pc
        self.file.append('g' + '0' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1

    def jmne(self,a,b):
        global pc
        self.file.append('e' + '0' + hex(self.ChooseReg(a))[2::] + hex(self.ChooseReg(b))[2::] + ' ')
        pc += 1







