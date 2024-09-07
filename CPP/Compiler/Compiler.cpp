#include <iostream>
#include <fstream>
#include "Lexer.h"

int main()
{
    std::string filePath = "C:\\GitHub_Repos\\PLTest\\input.txt";
    std::ifstream ifs(filePath);
    Lexer lexer(ifs);

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