#include "tokentype.hpp"

std::string type_string(const Type& type)
{
    switch(type){
        case Type::DIVIDE:
            return "DIVIDE";
        case Type::EQUAL:
            return "EQUAL";
        case Type::MINUS:
            return "MINUS";
        case Type::MODULO:
            return "MODULO";
        case Type::MULTIPLY:
            return "MULTIPLY";
        case Type::PLUS:
            return "PLUS";
        case Type::POWER:
            return "POWER";
        case Type::DECIMAL:
            return "DECIMAL";
        case Type::INTEGER:
            return "INTEGER";
        case Type::VARIABLE:
            return "INTEGER";
        case Type::LEFT_PAREN:
            return "LEFT_PAREN";
        case Type::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case Type::END_OF_INPUT:
            return "END_OF_INPUT";
        case Type::UNRECOGNIZED:
            return "UNRECOGNIZED";
        default:
            return "UNRECOGNIZED";
    }
}

std::unordered_map<std::string, Type> make_keywords()
{
    std::unordered_map<std::string, Type> keywords;
    keywords["/"] = Type::DIVIDE;
    keywords["="] = Type::EQUAL;
    keywords["-"] = Type::MINUS;
    keywords["%"] = Type::MODULO;
    keywords["*"] = Type::MULTIPLY;
    keywords["+"] = Type::PLUS;
    keywords["^"] = Type::POWER;
    keywords["("] = Type::LEFT_PAREN;
    keywords[")"] = Type::RIGHT_PAREN;
    keywords["UNRECOGNIZED"] = Type::UNRECOGNIZED;
    return keywords;
}
