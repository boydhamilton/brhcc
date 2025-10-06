#pragma once

// std lib
#include<string>
#include<vector>
#include<optional>
#include<iostream>


// definitions 
enum class TokenType {
	exit,
	int_lit,
	semi
};

typedef struct {
	TokenType type;
	std::optional<std::string> val;
} Token;



class Tokenizer {

    public:
        inline explicit Tokenizer(const std::string& src)
           : m_src(std::move(src))
           {

           }

           inline std::vector<Token> tokenize() {

                std::vector<Token> tokens;
                std::string buf;

                while(peek().has_value()){
                    if(std::isalpha(peek().value())){
                        buf.push_back(consume());
                        while(peek().has_value() && std::isalnum(peek().value())){
                            buf.push_back(consume());
                        }
                        if(buf == "exit"){
                            tokens.push_back({.type = TokenType::exit});
                            buf.clear();
                            continue;
                        }else{
                            std::cerr << "Error in keyword tokenization" << std::endl;
                            std::cout << buf <<" | "<< buf.length() << std::endl;
                            exit(EXIT_FAILURE);
                        }

                    }else if(std::isdigit(peek().value()) ){
                        buf.push_back(consume());
                        while(peek().has_value() && std::isdigit(peek().value() )){
                            buf.push_back(consume());
                        }
                        tokens.push_back({ .type= TokenType::int_lit, .val = buf});
                        buf.clear();
                        continue;

                    }else if(peek().value() == ';'){
                        consume(); // make sure you consume every token so you move through the program properly
                        tokens.push_back( {.type=TokenType::semi} );
                        continue;

                    }else if(isspace(peek().value())){
                        consume();
                        continue;
                    }else{
                        std::cerr << "Error in typewise tokenization" << std::endl;
                    }
                }
                m_index = 0; // reset
                return tokens;

           }

    private:

        [[nodiscard]] inline std::optional<char> peek(int ahead = 1) const { 
            /* 
            SUPER interesting method def, so let's break it down as this is for learning: 
            nodiscard means we get compilation warning if we don't use returned value. 
            ahead = 1 means it'll default to 1, but you can overload to specify how many values you want to peek ahead
            the const that follows means this is a CONSTANT method, it cant alter fields in the class
            */
            if(m_index + ahead > m_src.length()){
                return {};
            }else{
                return m_src.at(m_index);
            }
        }

        inline char consume(){
            return m_src.at(m_index++);
        }

        const std::string m_src;
        size_t m_index = 0;
};