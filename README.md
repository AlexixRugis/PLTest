# Programming language experiment

There is a small intermediate code compiler and interpreter for this code. Everything is written in python.

## How to use

Just edit the file input.txt

**The code must be between curly brackets**

Run whole workflow
```
.\compile_and_run.bat
```
Run only compilation (compiled code saved in program.txt)
```
python ./compile.py
```
Run only virtual machine (runs code from program.txt)
```
python ./vm.py
```

## Operators

Binary
```+ - * /```

Unary
```+ -```

Comparison
```<```

Control
```if else while```

Functions
```print```

## Examples

### Print 

Input.txt
```
{
    a = 10;
    _b34 = 120;
    print('Hello world!\n');
    print(a);
    print('\n');
    print(_b34);
    print('\n');
    print(120*-3/a);
}
```

Output:
```
Hello world!
10
120
-36
```

### if (else)

Input.txt
```
{
    age = 17;

    if (age < 18) {
        print('No\n');
    } else {
        print('Yes\n');
    }
}
```

Output
```
No
```

### While

Input.txt
```
{
    a = 1;
    b = 1;
    while (b < 100) {
        c = a + b;
        print(c);
        print('\n');
        a = b;
        b = c;
    }

    print('End\n');
}
```

Output
```
2
3
5
8
13
21
34
55
89
144
End
```