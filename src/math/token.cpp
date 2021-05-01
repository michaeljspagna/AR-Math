#include "token.hpp"

auto Token::token_string(const Token& token) -> std::string
{
	std::string type = type_string(token.type);
	std::string builder = "[type: ";
	builder += type;
	builder += ", value: ";
	builder += token.value;
	builder += "]\n";
							
	return builder;
}

auto Token::make(Type type, std::string value) -> Token::Token
{
	Token token = {
		 type
		,value
	};
	return token;
}

auto Token::make(Type type, char value) -> Token::Token
{
	return make(type, std::string(1,value));
}
