import math
import sys

DEBUG = False

class SyntaxRule:
    def __init__(self, rule: list[str], replacement: str, precedence: int, name: str = ''):
        self.rule = rule
        self.replacement = replacement
        self.precedence = precedence
        self.name = name
        
    def test_stack_match(self, stack: list[str]) -> bool:
        if len(stack) < len(self.rule):
            return False
        
        valid = True
        for i in range(1, len(self.rule)+1):
            if self.rule[-i] != stack[-i]:
                valid = False
                break
            
        return valid
    
    def test_right_precedence(self, current_token: str, next_token: str, left_precedence: int) -> bool:
        if len(self.rule) < 2:
            return False
        
        return self.rule[0] == current_token and self.rule[1] == next_token and self.precedence > left_precedence
    
    def __len__(self) -> int:
        return len(self.rule)
    
    def __getitem__(self, key: int) -> str:
        return self.rule[key]

rules = [
    SyntaxRule(['id',], 't', 10000, 'terming'),
    SyntaxRule(['name',], 'named_expr', 9999, 'named-expr'),
    SyntaxRule(['named_expr', '='], 'assignment_begin', 9998, 'assignment-begin'),
    SyntaxRule(['named_expr',], 't', 9997, 'denaming'),
    SyntaxRule(['(','t',')',], 't', 9996, 'bracket-expr'),
    SyntaxRule(['t', '^', 't'], 't', 9995, 'pow'),
    SyntaxRule(['-', 't',], 't', 9994, 'uminus'),
    SyntaxRule(['t', '*', 't'], 't', 9993, 'mult'),
    SyntaxRule(['t', '/', 't'], 't', 9993, 'div'),
    SyntaxRule(['t', '+', 't'], 't', 9992, 'sum'),
    SyntaxRule(['t', '-', 't'], 't', 9992, 'sub'),
    SyntaxRule(['assignment_begin', 't'], 'e', 0, 'assignment'),
]

def parse_input(inp_str : str):
    row = []
    if len(inp_str) == 0:
        return row
    
    ind = 0
    
    symbol_tokens = "+-*^/()="
    while ind < len(inp_str):
        if inp_str[ind] == ' ':
            ind+=1
        elif inp_str[ind] in symbol_tokens:
            row.append((inp_str[ind],))
            ind+=1
        elif inp_str[ind].isdigit():
            val = 0
            while ind < len(inp_str) and inp_str[ind].isdigit():
                val = 10*val + int(inp_str[ind])
                ind+=1
            row.append(('id', val))
        elif inp_str[ind].isalpha() or inp_str[ind] == '_':
            st = ''
            while ind < len(inp_str) and (inp_str[ind].isalnum() or inp_str[ind] == '_'):
                st += inp_str[ind]
                ind+=1
            row.append(('name', st))
        else:
            print('Неизвестный символ: ' + inp_str[ind])
            sys.exit(-1)
        
        
    return row
    

vars = {
    'PI': math.pi
}

def exec_single_string(inp_str):
    row = parse_input(inp_str)
    if DEBUG:
        print(row)    

    stack = []
    value_stack = []

    for ind, token in enumerate(row):
        stack.append(token[0])
        if DEBUG:
            print(stack, row[ind+1:])
        while True:
            # Поиск подходящего правила свертки
            repl_rule = None
            for syntax_rule in rules:
                if syntax_rule.test_stack_match(stack):
                    if not repl_rule or len(syntax_rule) > len(repl_rule):
                        repl_rule = syntax_rule
                        
            # Разрешаем shift-reduce конфликт в пользу правила с большим приоритетом-
            prefer_shift = False
            if not repl_rule:
                prefer_shift = True
            else:        
                for syntax_rule in rules:
                    if ind != len(row) - 1 and syntax_rule.test_right_precedence(stack[-1], row[ind+1][0], repl_rule.precedence):
                        prefer_shift = True
                        break
            
            if prefer_shift:
                break
            
            stack = stack[:-len(repl_rule)] + [repl_rule.replacement,]
            if repl_rule.name == 'terming':
                value_stack.append(token[1])
            elif repl_rule.name == 'named-expr':
                value_stack.append(token[1])
            elif repl_rule.name == 'assignment':
                op1 = value_stack[-1]
                op2 = value_stack[-2]
                vars[op2] = op1
                value_stack = value_stack[:-2]
            elif repl_rule.name == 'denaming':
                var_name = value_stack[-1]
                var_val = vars.get(var_name, None)
                if not var_val:
                    print('Неизвестное значение: ' + str(var_name))
                    sys.exit(-1)
                value_stack = value_stack[:-1] + [var_val,]
            elif repl_rule.name == 'uminus':
                val = value_stack[-1]
                value_stack = value_stack[:-1] + [-val,]
            elif repl_rule.name == 'mult':
                op1 = value_stack[-1]
                op2 = value_stack[-2]
                value_stack = value_stack[:-2] + [op1*op2,]
            elif repl_rule.name == 'pow':
                op1 = value_stack[-1]
                op2 = value_stack[-2]
                value_stack = value_stack[:-2] + [op2**op1,]
            elif repl_rule.name == 'div':
                op1 = value_stack[-1]
                op2 = value_stack[-2]
                value_stack = value_stack[:-2] + [op2/op1,]
            elif repl_rule.name == 'sum':
                op1 = value_stack[-1]
                op2 = value_stack[-2]
                value_stack = value_stack[:-2] + [op1+op2,]
            elif repl_rule.name == 'sub':
                op1 = value_stack[-1]
                op2 = value_stack[-2]
                value_stack = value_stack[:-2] + [op2-op1,]
            
            if DEBUG:
                print(value_stack)
                print(stack, row[ind+1:])

    if len(stack) != 1:
        print('Введено некорректное выражение!')
    else:
        if len(value_stack) == 1:
            print(value_stack[0])
        
while True:
    exec_single_string(input('Введите выражение: '))
    if DEBUG:
        print(vars)
