#ifndef LEXER_H
    #define LEXER_H
    
    #include <string>
    #include <unordered_map>
    #include <vector>
    #include "tokentype.hpp"
    #include "token.hpp"
    
    class Lexer
    {
        private:
            std::string buffer;
            std::unordered_map<std::string, Type> keywords;
            int position;
            char character;

            auto feed(const std::string&) -> void;
            auto next_token() -> Token::Token;
            auto read_character() -> void;
            auto peek_character() -> char;
            auto number(Token::Token&) -> void;
            auto operation(Token::Token&) -> void;
            auto parenthesis(Token::Token&) -> void;
            
            auto skip_whitespace() -> void;
            auto read_number() -> std::string;

        public:
            Lexer();
            ~Lexer();
            
            auto cli() -> void;
            auto run(const std::string&) -> std::vector<Token::Token>;
    };
    
#endif /* LEXER_H */