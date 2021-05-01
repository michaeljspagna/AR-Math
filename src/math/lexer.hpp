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

            void feed(const std::string&);
            Token::Token next_token();
            void read_character();
            char peek_character();
            void skip_whitespace();
            void identifier(Token::Token&);
            void number(Token::Token&);
            void string(Token::Token&);
            void operation(Token::Token&);
            void delimeter(Token::Token&);
            std::string read_identifier();
            std::string read_number();
            std::string read_string();
            Type identifier_type(const std::string&);

        public:
            Lexer();
            ~Lexer();
            
            void cli();
            std::vector<Token::Token> run(const std::string&);
    };

    
#endif /* LEXER_H */