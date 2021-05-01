#ifndef TOKENTYPE_HPP
    #define TOKENTYPE_HPP
    
    #include <string>
    #include <unordered_map>

    enum Type 
    {
        // Math Operations
         DIVIDE // /
        ,EQUAL // =
        ,MINUS // -
        ,MODULO // %
        ,MULTIPLY // x
        ,PLUS // +
        ,POWER // ^
        // Identifier and Literals
        ,DECIMAL // 12.3
        ,INTEGER // 123
        ,VARIABLE // x
        // Delimiters
        ,LEFT_PAREN // (
        ,RIGHT_PAREN // )
        // Special
        ,END_OF_INPUT
        ,UNRECOGNIZED
    };

    auto type_string(const Type&) -> std::string;
    auto make_keywords() -> std::unordered_map<std::string, Type>;
    
#endif /* TOKENTYPE_HPP */