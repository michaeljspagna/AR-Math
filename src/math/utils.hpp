#ifndef UTILS_HPP
	#define UTILS_HPP
    
	namespace Utils
	{
		auto is_alpha(char) -> bool;
		auto is_comma(char) -> bool;
		auto is_digit(char) -> bool;
		auto is_dot(char) -> bool;
		auto is_operation(char) -> bool;
        auto is_parenthesis(char) -> bool;
		auto is_whitespace(char) -> bool;
	}

#endif /* UTILS_HPP */