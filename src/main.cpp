
// std lib
#include<iostream>
#include<fstream>
#include<sstream>

// local 
#include "tokenizer.hh"
#include "parser.hh"
#include "generation.hpp"

using namespace std;


/*
prec : requires two files, input .c file and output .s file names
postc: outputs .s file into above file name or otherwise throws an error
*/
int main(int argc, char* argv[]){
	if(argc != 3){ // num args we use + 1
		cerr << "Incorrect number of aargaaas" << endl;
		return EXIT_FAILURE;
	}



	string contents;
	{ // reading input scope

		fstream in(argv[1], ios::in); // open input .c file
		stringstream content_stream;

		content_stream << in.rdbuf();
		in.close();
		contents = content_stream.str();
	}

	Tokenizer tokenizer(move(contents));
	vector<Token> tokens = tokenizer.tokenize();

	Parser parser(std::move(tokens));
	optional<node::Exit> ast = parser.parse();

	if(!ast.has_value()){
		cerr << "No exit statement found" << endl;
		exit(EXIT_FAILURE);
	}

	Generator generator(ast.value());
	{
		fstream out(argv[2], ios::out); // open out .s file
		out << generator.generate_asm();
		out.close();
	}


	return EXIT_SUCCESS;
}
