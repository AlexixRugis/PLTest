import sys
import time
class WM(object):
    def __init__(self, file):
        self.file = file
        self.program = self.file.read()
        self.program = self.program.split(' ')
        self.Ram = [0]*1024
        self.stack = [0]*1024
        self.sp = -1
        self.pc = 0

    def push(self, val):
        if self.sp == 1023:
            raise Exception('stack overflow')
        self.sp += 1
        self.stack[self.sp] = val
    
    def pop(self):
        if self.sp == -1:
            raise Exception('stack empty')
        val = self.stack[self.sp]
        self.sp -= 1
        return val

    def Run(self):
        while True:
            if self.program[self.pc] == 'EOP':
                break

            elif self.program[self.pc] == 'push':
                self.push(int(self.program[self.pc + 1]))
                self.pc += 2
                
            elif self.program[self.pc] == 'pop':
                self.pop()
                self.pc += 1
            
            elif self.program[self.pc] == 'load':
                self.push(self.Ram[int(self.program[self.pc + 1])])
                self.pc += 2
                
            elif self.program[self.pc] == 'store':
                self.Ram[int(self.program[self.pc + 1])] = self.pop()
                self.pc += 2

            elif self.program[self.pc] == 'sum':
                self.push(self.pop() + self.pop()) 
                self.pc += 1

            elif self.program[self.pc] == 'sub':
                self.push(self.pop() - self.pop())
                self.pc += 1

            elif self.program[self.pc] == 'mult':
                self.push(self.pop() * self.pop())
                self.pc += 1
                                
            elif self.program[self.pc] == 'div':
                self.push(self.pop() // self.pop())
                self.pc += 1

            elif self.program[self.pc] == 'ilt':
                if self.pop() < self.pop():
                    self.push(1)
                else:
                    self.push(0)
                self.pc += 1

            elif self.program[self.pc] == 'jme':
                adr = self.pop()
                if self.pop() == self.pop():
                    self.pc = adr
                else:
                    self.pc += 1

            elif self.program[self.pc] == 'jma':
                self.pc = self.pop()

            elif self.program[self.pc] == 'printch':
                print(chr(self.pop()), end='')
                self.pc += 1
            
            elif self.program[self.pc] == 'printnum':
                print(self.pop(), end='')
                self.pc += 1

            else:
                print('Unknown command!')
                print(self.program[self.pc])
                print(self.pc)
                sys.exit(-1)

with open("program.txt",'r') as file:
    wm = WM(file)
    start_time = time.time()
    wm.Run()
    print("--- %s seconds ---" % (time.time() - start_time))
    file.close()