#include <iostream>
#include "Lexer.h"

int main()
{
    std::string filePath = "C:\\GitHub_Repos\\PLTest\\input.txt";
    Lexer lexer(filePath);

    while (true)
    {
        LexerToken token = lexer.NextToken();
        std::cout << ToString(token.Type()) << ' ' << token.Value() << std::endl;

        if (token.Type() == LexerTokenType::ENDOFFILE)
        {
            break;
        }
    }
}