
#include "lexer.hh"

// debug libs
#include<iostream>

using namespace std;


/*
* requires: source code
* returns: vector of tokens in order
*/
vector<Token> tokenize(const string& str){

	vector<Token> tokens;
	string buf;


	for(int i=0; i<str.length(); i++){
		char c = str.at(i);

		// branching off type of char
		if(isalpha(c)){
			buf.push_back(c);
			i++;
			while( isalnum(str.at(i)) ){
				buf.push_back(str.at(i));
				i++;
			}
			i--;
			if(buf == "return"){
				tokens.push_back({.type=TokenType::_return});
				buf.clear();
				continue;
			}
		}
		else if(isdigit(c)){
			int val = 1;
			buf.push_back(c);
			i++;
			while( isdigit(str.at(i)) ){
				char cc = str.at(i);
				buf.push_back(cc);
				i++;
			}
			i--;
			tokens.push_back({.type=TokenType::int_lit, .val=buf});
			buf.clear();
		}else if(c == ';'){
			tokens.push_back({.type=TokenType::semi});
		}
		else if(isspace(c)){
			continue;
		}
		else{
			cerr << "Syntax error in lexer tokenization, unknown type" << endl;
			exit(EXIT_FAILURE); // syscall we can use when we have to exit and not in int main
		}
	}
	
	return tokens;

}

string token_to_asm(vector<Token>& tokens){

	string output = "global _start\n_start:";
	for(int i=0; i<tokens.size(); i++){
		const Token& token = tokens.at(i);
		if(token.type == TokenType::_return){
			if( i +1 < tokens.size() && tokens.at(i +1).type == TokenType::int_lit){
				if( i +2 < tokens.size() && tokens.at(i +2).type == TokenType::semi){
					output += "\tmov rax, 60\n";
					output += "\tmov rdi, " + *tokens.at(i +1).val + "\n";
				}
			}
			output += "\tsyscall";
		}
	}

	return output;

}