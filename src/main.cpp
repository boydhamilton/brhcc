
// std lib
#include<iostream>
#include<fstream>
#include<sstream>

// local 
#include "lexer.hh"

using namespace std;

/*
prec : requires two files, input .c file and output .s file names
postc: outputs .s file into above file name or otherwise throws an error
*/
int main(int argc, char* argv[]){
	if(argc != 3){ // num args we use + 1
		cerr << "Incorrect number of args" << endl;
		return EXIT_FAILURE;
	}
	cout << argv[1] << endl;

	string contents;
	{ // reading input scope

	fstream in(argv[1], ios::in); // open input .c file
	stringstream content_stream;

	content_stream << in.rdbuf();
	in.close();
	contents = content_stream.str();
	}

	vector<Token> tokens = tokenize(contents);
	string outputted_asm = token_to_asm(tokens);

	{ // generating output scope

	fstream out(argv[2], ios::out); // open out .s file
	out << outputted_asm;
	out.close();
	}

	return EXIT_SUCCESS;
}
