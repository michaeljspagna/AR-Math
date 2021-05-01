#include <cctype>
#include "utils.hpp"

/*
 * Returns true if input character is an alphabetic or underscore character [a-z|A-Z|_]
 * Returns false if input character is not an alphabetic or underscore character
 */
auto Utils::is_alpha(const char character) -> bool
{
	return std::isalpha(character);
}

/*
 * Returns true if input character is a digit character [0-9]
 * Returns false if input character is not a digit character
 */
auto Utils::is_digit(char character) -> bool
{
	return std::isdigit(character);
}

/*
 * Returns true if input character is a dot character [.]
 * Returns false if input character is not a dot character
 */
auto Utils::is_dot(char character) -> bool
{
	return character == '.';
}

/*
 * Returns true if input character is an operation character [=|+|-|*|/|%|>|<|!]
 * Returns false if input character is not an operation character
 */
auto Utils::is_operation(char character) -> bool
{
	return (character == '/' || character == '=' || character == '-' || 
			character == '%' || character == '*' || character == '+' || 
			character == '^');
}

/*
 * Returns true if input character is a paren character ()
 * Returns false if input character is not a paren character
 */
auto Utils::is_paren(const char character) -> bool
{
	return (character == '(' || character == ')');
}

/*
 * Returns true if input character is a whitespace character
 * Returns false if input character is not a whitespace character
 */
auto Utils::is_whitespace(const char character) -> bool
{
	return (character == ' ' || character == ',');
}