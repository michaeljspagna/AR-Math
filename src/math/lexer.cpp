#include <iostream>
#include "lexer.hpp"       
#include "utils.hpp"
#include "error.hpp"

/*
 *Constructor
 *
 *
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
 *
 *
 */
Lexer::~Lexer(){}

/*
 *Runs Lexer Command Line Interface
 *
 *
 */
void Lexer::cli(){
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
std::vector<Token::Token> Lexer::run(const std::string& input)
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
 *
 */
void Lexer::feed(const std::string& input)
{
	buffer = input;
	position = -1;
	Lexer::read_character();
}

/*
 *Returns the next token of the Lexer buffer
 *
 *output: next buffer token
 */
Token::Token Lexer::next_token()
{
	Lexer::skip_whitespace();
	if(character == '\0'){
		return Token::make(Type::END_OF_INPUT, character);
	}

	Token::Token token;
	if(Utils::is_alpha(character)){
		Lexer::identifier(token);
	}else if(Utils::is_digit(character)){
		Lexer::number(token);
	}else if(Utils::is_quote(character)){
		Lexer::string(token);
	}else if(Utils::is_semicolon(character)){
		token = Token::make(Type::SEMICOLON, character);
		Lexer::read_character();
	}else if(Utils::is_operation(character)){
		Lexer::operation(token);
	}else if(Utils::is_delimiter(character)){
		Lexer::delimeter(token);
	}else{
		token = Token::make(Type::UNRECOGNIZED, character);
		Lexer::read_character();
	}

	if (token.type == Type::UNRECOGNIZED){
		std::string error = ("ERROR, UNRECOGNIZED VALUE: { " + token.value + " }");
		Error::throw_error(error, -1, -1);
	}
	
	return token;
}

/*
 *Advances the position marker and updates character
 *
 *
 */
void Lexer::read_character()
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
 *
 *output: next character in buffer, '\0' if EoI
 */
char Lexer::peek_character()
{
	if(position+1 >= buffer.length()){
		return '\0';
	}

	return buffer.at(position+1);
}

/*
 *Skips successive whitespace characters
 *
 *
 */
void Lexer::skip_whitespace()
{
	while(character != '\0' &&
		 Utils::is_whitespace(character)){
		Lexer::read_character();
	}
}

/*
 *Tokenizes a number
 *input: token to store number token
 *
 */
void Lexer::number(Token::Token& token)
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
 *
 */
void Lexer::operation(Token::Token& token)
{
	char next = Lexer::peek_character();
	switch(character){
		case '=':
			switch(next){
				case '=':
					token = Token::make(Type::EQUAL, "==");
					Lexer::read_character();
				default:
					token = Token::make(Type::ASSIGN, character);
			}
			break;
		case '+':
			switch(next){
				case '+':
					token = Token::make(Type::INCREMENT, "++");
					Lexer::read_character();
				case '=':
					token = Token::make(Type::PLUS_ASSIGN, "+=");
					Lexer::read_character();
				default:
					token = Token::make(Type::PLUS, character);
			}
			break;
		case '-':
			switch(next){
				case '>':
					token = Token::make(Type::PRINT, "->");
					Lexer::read_character();
				case '-':
					token = Token::make(Type::DECREMENT, "--");
					Lexer::read_character();
				case '=':
					token = Token::make(Type::MINUS_ASSIGN, "-=");
					Lexer::read_character();
				default:
					token = Token::make(Type::MINUS, character);
			}
			break;
		case '*':
			switch(next){
				case '*':
					token = Token::make(Type::POWER, "**");
					Lexer::read_character();
				case '=':
					token = Token::make(Type::MULTIPLY_ASSIGN, "*=");
					Lexer::read_character();
				default:
					token = Token::make(Type::MULTIPLY, character);
			}
			break;
		case '/':
			switch(next){
				case '=':
					token = Token::make(Type::DIVIDE_ASSIGN, "/=");
					Lexer::read_character();
				default:
					token = Token::make(Type::DIVIDE, character);
			}
			break;
		case '%':
			switch(next){
				case '=':
					token = Token::make(Type::MODULO_ASSIGN, "%=");
					Lexer::read_character();
				default:
					token = Token::make(Type::MODULO, character);
			}
			break;
		case '>':
			switch(next){
				case '=':
					token = Token::make(Type::GREATER_EQUAL, ">=");
					Lexer::read_character();
				default:
					token = Token::make(Type::GREATER, character);
			}
			break;
		case '<':
			switch(next){
				case '=':
					token = Token::make(Type::LESS_EQUAL, "<=");
					Lexer::read_character();
				default:
					token = Token::make(Type::LESS, character);
			}
			break;
		case '!':
			switch(next){
				case '=':
					token = Token::make(Type::NOT_EQUAL, "!=");
					Lexer::read_character();
				default:
					token = Token::make(Type::NOT, character);
			}
			break;
		default:
			token = Token::make(Type::UNRECOGNIZED, "Unknown Operation");
	}
	Lexer::read_character();
}

/*
 *Tokenizes a delimeter
 *input: token to store delimeter token
 *
 */
void Lexer::delimeter(Token::Token& token)
{
	char next = Lexer::peek_character();
	switch(character){
		case '#':
			token = Token::make(Type::END_OF_INPUT, '\0');
			buffer = "";
			position = 0;
			character = ' ';
			break;
		case ',':
			token = Token::make(Type::COMMA, character);
			break;
		case '{':
			token = Token::make(Type::LEFT_BRACE, character);
			break;
		case '[':
			token = Token::make(Type::LEFT_BRACKET, character);
			break;
		case '(':
			token = Token::make(Type::LEFT_PAREN, character);
			break;
		case '}':
			token = Token::make(Type::RIGHT_BRACE, character);
			break;
		case ']':
			token = Token::make(Type::RIGHT_BRACKET, character);
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
 *Reads a sequention decimal or integer
 *
 *output: number
 */
std::string Lexer::read_number()
{
	bool found_dot = false;
	std::string identifier = "";
	while(Utils::is_digit(character) ||
		 Utils::is_dot(character)){
		if(Utils::is_dot(character)){
			if(found_dot) return "\0";
			found_dot = true;
		}
		identifier += character;
		Lexer::read_character();
	}
	return identifier;
}

int main(int argc, char const *argv[])
{
	Lexer l;
	l.cli();
	return 0;
}