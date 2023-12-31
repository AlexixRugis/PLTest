import sys

class Assembler(object):
    def __init__(self, input):
        self.pc = 0
        self.file = input

    def push(self, a):
        if a >= 0 and a <= 32767:
            self.file.append('push ')
            self.file.append(str(a) + ' ')
            self.pc += 2
        else:
            print("число выходит за границы допустимого диапазона!")
            
    def pop(self):
        self.file.append('pop ')
        self.pc += 1
        
    def load(self, addr):
        self.file.append('load ')
        self.file.append(str(addr) + ' ')
        self.pc += 2
        
    def store(self, addr):
        self.file.append('store ')
        self.file.append(str(addr) + ' ')
        self.pc += 2
        
    def sum(self):
        self.file.append('sum ')
        self.pc += 1
        
    def sub(self):
        self.file.append('sub ')
        self.pc += 1
        
    def mult(self):
        self.file.append('mult ')
        self.pc += 1
        
    def div(self):
        self.file.append('div ')
        self.pc += 1

    def ilt(self):
        self.file.append('ilt ')
        self.pc += 1
        
    def jme(self):
        self.file.append('jme ')
        self.pc += 1
        
    def jma(self):
        self.file.append('jma ')
        self.pc += 1
        
    def printch(self):
        self.file.append('printch ')
        self.pc += 1
        
    def printnum(self):
        self.file.append('printnum ')
        self.pc += 1
        
    def eop(self):
        self.file.append('EOP ')
        self.pc += 1