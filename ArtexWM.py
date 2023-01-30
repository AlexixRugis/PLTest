import sys
import time
class WM(object):
    def __init__(self, file):
        self.file = file
        self.program = self.file.read()
        self.program = self.program.split(' ')
        self.acc = 0
        self.adr = 0
        self.A = 0
        self.B = 0
        self.C = 0
        self.D = 0
        self.Ram = [0]*1024
        self.pc = 0

    def ChooosReg(self, reg):
        if str(reg) == '1':
            return self.acc
        elif str(reg) == '8':
            return self.pc
        elif str(reg) == '2':
            return self.adr
        elif str(reg) == '3':
            return self.A
        elif str(reg) == '4':
            return self.B
        elif str(reg) == '5':
            return self.C
        elif str(reg) == '6':
            return self.D
        elif str(reg) == '7':
            return self.Ram[self.adr]
        else:
            print('choose reg a error!')
            self.file.close()
            sys.exit(0)

    def mov(self, a, b):
        if str(b) == '1':
            self.acc = a
        elif str(b) == '8':
            self.pc = a
        elif str(b) == '2':
            self.adr = a
        elif str(b) == '3':
            self.A = a
        elif str(b) == '4':
            self.B = a
        elif str(b) == '5':
            self.C = a
        elif str(b) == '6':
            self.D = a
        elif str(b) == '7':
            self.Ram[self.adr] = a
        else:
            print('choose reg a error!')
            self.file.close()
            sys.exit(0)

    def Run(self):

        while True:
            if self.program[self.pc] == 'EOP':
                break

            elif self.program[self.pc] == 'mov':
                self.mov(self.ChooosReg(self.program[self.pc + 1]), self.program[self.pc + 2])
                self.pc += 3

            elif self.program[self.pc] == 'loadacc':
                self.acc = int(self.program[self.pc + 1])
                self.pc += 2

            elif self.program[self.pc] == 'sum':
                sum = self.ChooosReg(self.program[self.pc + 1]) + self.ChooosReg(self.program[self.pc + 2])
                self.mov(sum, self.program[self.pc + 1])
                self.pc += 3

            elif self.program[self.pc] == 'sub':
                sub = self.ChooosReg(self.program[self.pc + 1]) - self.ChooosReg(self.program[self.pc + 2])
                self.mov(sub, self.program[self.pc + 1])
                self.pc += 3

            elif self.program[self.pc] == 'ilt':
                if self.ChooosReg(self.program[self.pc + 1]) < self.ChooosReg(self.program[self.pc + 2]):
                    self.A = 1
                else:
                    self.A = 0
                self.pc += 3

            elif self.program[self.pc] == 'jme':
                if self.ChooosReg(self.program[self.pc + 1]) == self.ChooosReg(self.program[self.pc + 2]):
                    self.pc = self.adr

                else:
                    self.pc += 3

            elif self.program[self.pc] == 'jma':
                self.pc = self.adr

            elif self.program[self.pc] == 'print':
                if self.program[self.pc + 1] == 'char':
                    print(chr(int(self.program[self.pc + 2])), end='')
                elif self.program[self.pc + 1] == 'reg':
                    print(self.ChooosReg(self.program[self.pc + 2]), end='')
                self.pc += 3

            else:
                print('Unknown command!')
                print(self.program[self.pc])
                print(self.pc)

with open("program.txt",'r') as file:
    wm = WM(file)
    start_time = time.time()
    wm.Run()
    print("--- %s seconds ---" % (time.time() - start_time))
    file.close()