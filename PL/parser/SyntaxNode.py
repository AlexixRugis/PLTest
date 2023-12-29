class SyntaxNode:
    def __init__(self, kind, value = None, op1 = None, op2 = None, op3 = None):
        self.kind = kind
        self.value = value
        self.op1 = op1
        self.op2 = op2
        self.op3 = op3