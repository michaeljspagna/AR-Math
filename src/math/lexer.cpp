#include <iostream>
#include "lexer.hpp"       
#include "utils.hpp"
#include "error.hpp"

/*
 *Constructor
 */
Lexer::Lexer()
{	
	this->buffer = "";
	this->keywords = make_keywords();
	this->position = -1;
	this->character = ' ';
}

/*
 *Destructor
 */
Lexer::~Lexer(){}

/*
 *Runs Lexer Command Line Interface
 */
auto Lexer::cli() -> void{
	int i;
	std::vector<Token::Token> v;
	std::string input;
	while(true){
		std::cout << "lexer> ";
		std::getline(std::cin, input);
		if(input == "exit()") break;
		v = run(input);
		for(i=0; i<v.size(); i++){
			std::cout << Token::token_string(v[i]) << std::endl;
		}
	}
}

/*
 *Tokenizes the input string
 *input: string to tokenize
 *output: vector of tokens generated from input string
 */
auto Lexer::run(const std::string& input) -> std::vector<Token::Token>
{
	std::vector<Token::Token> tokens;
	Token::Token token;

	Lexer::feed(input);
	do{
		token = this->Lexer::next_token();
		tokens.push_back(token);
	}while(token.type != Type::END_OF_INPUT);
	
	return tokens;
}

/*
 *Sets Lexer buffer
 *input: string to be tokenized
 */
auto Lexer::feed(const std::string& input) -> void
{
	buffer = input;
	position = -1;
	Lexer::read_character();
}

/*
 *Returns the next token of the Lexer buffer
 *output: next buffer token
 */
auto Lexer::next_token() -> Token::Token
{
	Lexer::skip_whitespace();
	if(character == '\0'){
		return Token::make(Type::END_OF_INPUT, character);
	}

	Token::Token token;
	if(Utils::is_digit(character)){
		Lexer::number(token);
	}else if(Utils::is_parenthesis(character)){
		Lexer::parenthesis(token);
	}else if(Utils::is_operation(character)){
		Lexer::operation(token);
	}else{
		token = Token::make(Type::UNRECOGNIZED, character);
		Lexer::read_character();
	}

	if (token.type == Type::UNRECOGNIZED){
		std::string error = ("ERROR, UNRECOGNIZED VALUE: { " + token.value + " }");
		Error::throw_error(error);
	}
	
	return token;
}

/*
 *Advances the position marker and updates character
 */
auto Lexer::read_character() -> void
{
	if(position+1 >= buffer.length())
	{
		character = '\0';
		return;
	}
	position++;
	character = buffer.at(position);
}

/*
 *Checks the next character in the buffer
 *output: next character in buffer, '\0' if EoI
 */
auto Lexer::peek_character() -> char
{
	if(position+1 >= buffer.length()){
		return '\0';
	}

	return buffer.at(position+1);
}

/*
 *Tokenizes a number
 *input: token to store number token
 */
auto Lexer::number(Token::Token& token) -> void
{
	Type type;
	std::string value = Lexer::read_number();
	if (value == "\0"){
		type = Type::UNRECOGNIZED;
		value = "INVALID NUMBER";
	}else if(value.find('.') != std::string::npos){
		type = Type::DECIMAL;
	}else{
		type = Type::INTEGER;
	}
	token = Token::make(type, value);
}

/*
 *Tokenizes an operation
 *input: token to store operation token
 */
auto Lexer::operation(Token::Token& token) -> void
{
	char next = Lexer::peek_character();
	switch(character){
		case '/':
			token = Token::make(Type::DIVIDE, character);
			break;
		case '=':
			token = Token::make(Type::EQUAL, character);
			break;
		case '-':
			token = Token::make(Type::MINUS, character);
			break;
		case '%':
			token = Token::make(Type::MODULO, character);
			break;
		case '*':
			token = Token::make(Type::MULTIPLY, character);
			break;
		case '+':
			token = Token::make(Type::PLUS, character);
			break;
		case '^':
			token = Token::make(Type::POWER, character);
			break;
		default:
			token = Token::make(Type::UNRECOGNIZED, "Unknown Operation");
	}
	Lexer::read_character();
}

/*
 *Tokenizes a paren
 *input: token to store paren token
 */
auto Lexer::parenthesis(Token::Token& token) -> void
{
	char next = Lexer::peek_character();
	switch(character){
		case '(':
			token = Token::make(Type::LEFT_PAREN, character);
			break;
		case ')':
			token = Token::make(Type::RIGHT_PAREN, character);
			break;
		default:
			token = Token::make(Type::UNRECOGNIZED, "Unrecognized Delimiter");
	}
	Lexer::read_character();
}

/*
 *Skips successive whitespace characters
 */
auto Lexer::skip_whitespace() -> void
{
	while(character != '\0' &&
		 Utils::is_whitespace(character)){
		Lexer::read_character();
	}
}

/*
 *Reads a sequention decimal or integer
 *output: number
 */
auto Lexer::read_number() -> std::string
{
	bool found_dot = false;
	std::string number = "";
	while(Utils::is_digit(character) || Utils::is_dot(character) 
									 ||	Utils::is_comma(character)){
		if(Utils::is_comma(character)){
			Lexer::read_character();
			continue;
		}
		if(Utils::is_dot(character)){
			if(found_dot) return "\0";
			found_dot = true;
		}
		number += character;
		Lexer::read_character();
	}
	return number;
}
