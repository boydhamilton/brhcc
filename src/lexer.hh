

#include<optional>
#include<vector>
#include<string>
#include<cmath>


enum class TokenType {

	_return,
	int_lit,
	semi

};

typedef struct {
	TokenType type;
	std::optional<std::string> val;
} Token;


std::vector<Token> tokenize(const std::string& str);

std::string token_to_asm(std::vector<Token>& tokens);