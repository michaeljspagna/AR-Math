/**
 * @file parser.hpp
 * @author your name (you@domain.com)
 * @brief NOT ACTUAL FUNCTIONALITY JUST ENOUGH TO MAKE IT WORK AND TEST *OTHER PARTS OF CODE
 * @version 0.1
 * @date 2021-05-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PARSER_HPP
    #define PARSER_HPP
    
    #include <string>
    #include <unordered_map>
    #include <vector>
    #include "tokentype.hpp"
    #include "token.hpp"
    #include "lexer.hpp"
    
    class Parser
    {
        private:
            Lexer lexer;
        public:
            Parser();
            ~Parser();

            auto run(std::vector<Token::Token>) -> double;
            auto cli() -> void;
    };

#endif /* PARSER_HPP */