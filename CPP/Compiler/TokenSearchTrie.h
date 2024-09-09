#pragma once
#include <cstdint>
#include <unordered_map>
#include <string>
#include <initializer_list>
#include <optional>
#include "LexerToken.h"

namespace Lexer {
    class TokenSearchTrie final
    {
    public:
        class Searcher final
        {
        public:
            bool TryFeed(char c)
            {
                auto iter = m_Trie->m_Nodes[m_Index].find(c);
                if (iter == m_Trie->m_Nodes[m_Index].end())
                {
                    return false;
                }

                m_Index = iter->second;

                return true;
            }

            std::optional<TokenType> Value() const
            {
                return m_Trie->m_Terminals[m_Index];
            }

        private:
            const TokenSearchTrie* m_Trie;
            uint64_t m_Index;

            Searcher(const TokenSearchTrie* trie) : m_Trie(trie), m_Index(0) {}

            friend class TokenSearchTrie;
        };

        TokenSearchTrie(const std::initializer_list<std::pair<std::string, TokenType>>& values)
        {
            NewNode();

            for (const auto& v : values)
            {
                AddValue(v);
            }
        }

        void AddValue(const std::pair<std::string, TokenType>& value)
        {
            uint64_t index = 0;

            for (auto ch : value.first)
            {
                auto iter = m_Nodes[index].find(ch);
                if (iter != m_Nodes[index].end()) index = iter->second;
                else
                {
                    uint64_t newIndex = NewNode();
                    m_Nodes[index][ch] = newIndex;
                    index = newIndex;
                }
            }

            m_Terminals[index] = value.second;
        }

        std::optional<TokenType> HasValue(const std::string& value) const
        {
            uint64_t index = 0;

            for (auto ch : value)
            {
                auto iter = m_Nodes[index].find(ch);
                if (iter != m_Nodes[index].end()) index = iter->second;
                else return std::nullopt;
            }

            return m_Terminals[index];
        }

        Searcher GetSearcher() const
        {
            return Searcher(this);
        }

    private:
        std::vector<std::unordered_map<char, uint64_t>> m_Nodes;
        std::vector<std::optional<TokenType>> m_Terminals;

    private:
        uint64_t NewNode()
        {
            m_Nodes.push_back({});
            m_Terminals.push_back(std::nullopt);
            return m_Nodes.size() - 1;
        }
    };
}