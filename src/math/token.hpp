#ifndef TOKEN_HPP
    #define TOKEN_HPP

    #include <string>
    #include "tokentype.hpp"
    
    namespace Token
    {
        struct Token 
        {
            Type type;
            std::string value;
        };
    
        auto token_string(const Token&) -> std::string;
        auto make(Type, std::string) -> Token;
        auto make(Type, char) -> Token;
    }
    
#endif /* TOKEN_HPP */ 