#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "Lexer.h"

int main()
{
    std::string filePath = "C:\\GitHub_Repos\\PLTest\\input.txt";
    std::ifstream ifs(filePath);
    Lexer::Lexer lexer(ifs);
    std::vector<Lexer::Token> lexems;

    auto start = std::chrono::high_resolution_clock::now();

    while (lexems.size() == 0 || lexems.back().Type() != Lexer::TokenType::ENDOFFILE)
    {
        Lexer::Token token = lexer.NextToken();
        lexems.push_back(token);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: "
        << duration.count() << " microseconds" << std::endl;

    for (auto& v : lexems)
    {
        std::cout << ToString(v.Type()) << ' ' << v.Value() << "\n";
    }
}