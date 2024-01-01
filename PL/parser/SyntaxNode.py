class SyntaxNode:
    def __init__(self, kind, value = None, op1 = None, op2 = None, op3 = None):
        self.kind = kind
        self.value = value
        self.op1 = op1
        self.op2 = op2
        self.op3 = op3
        
    def get_str_kind(self, kind):
        a = ['VAR', 'CONST', 'STRING', 'ADD', 'SUB', 
            'MULT', 'DIV', 'LT', 'SET', 'PRINT', 'IF1', 
            'IF2', 'WHILE', 'EMPTY', 'SEQ', 'EXPR', 'PROG']
        return a[kind]
        
    def pretty_print(self, indent=''):
        print(indent + self.get_str_kind(self.kind))
        indent += '|'
        if self.op1 and isinstance(self.op1, SyntaxNode):
            self.op1.pretty_print(indent)
        if self.op2 and isinstance(self.op2, SyntaxNode):
            self.op2.pretty_print(indent)
        if self.op3 and isinstance(self.op3, SyntaxNode):
            self.op3.pretty_print(indent)