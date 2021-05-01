/**
 * @file parser.cpp
 * @author your name (you@domain.com)
 * @brief NOT ACTUAL FUNCTIONALITY JUST ENOUGH TO MAKE IT WORK AND TEST *OTHER PARTS OF CODE
 * @version 0.1
 * @date 2021-05-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "parser.hpp"
#include <cmath>
#include <iostream>

Parser::Parser()
{
    lexer = Lexer();
}

Parser::~Parser(){}

auto Parser::run(std::vector<Token::Token> vec) -> double
{
    double op1 = std::stod(vec[0].value);
    double op2 = std::stod(vec[2].value);
    double out;
    switch(vec[1].type){
        case(Type::DIVIDE):
            out = op1/op2;
            break;
        case(Type::MINUS):
            out = op1-op2;
            break;
        case(Type::MODULO):
            out = -696969;
            break;
        case(Type::MULTIPLY):
            out = op1*op2;
            break;
        case(Type::PLUS):
            out = op1+op2;
            break;
        case(Type::POWER):
            out = std::pow(op1,op2);
            break;
        default:
            out = -696969;
            break;
    }
    return out;
}

/*
 *Runs Lexer Command Line Interface
 */
auto Parser::cli() -> void{
	int i;
	double result;
	std::string input;
	while(true){
		std::cout << "Parser> ";
		std::getline(std::cin, input);
		if(input == "exit()") break;
		result = run(lexer.run(input));
		std::cout << result << '\n';
	}
}

int main(int argc, char const *argv[])
{
	Parser p;
	p.cli();
	return 0;
}
