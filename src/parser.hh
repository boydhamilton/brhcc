
#pragma once

// std lib
#include<string>
#include<vector>
#include<optional>
#include<iostream>

// local 
#include "tokenizer.hh"


// definitions
namespace node {

    struct Expr{
        Token int_lit;
    };

    struct Exit{
        Expr expr;  
    };

    
}


class Parser {
    public:
        inline explicit Parser(std::vector<Token> tokens)
        : m_tokens(std::move(tokens)){

        }

        std::optional<node::Expr> parse_expr(){

            if(peek().has_value() && peek().value().type == TokenType::int_lit){
                return node::Expr{.int_lit = consume()} ;
            }else{
                return {};
            }

        }

        std::optional<node::Exit> parse(){ // returns the ROOT NODE, refer to nodes/grammar.md to see why ours is what it is
            std::optional<node::Exit> exit_node;
            while(peek().has_value()){
                if(peek().value().type == TokenType::exit){
                    consume();
                    if(auto node_expr = parse_expr() ){
                        exit_node = node::Exit{.expr = node_expr.value() };
                    }else{
                        std::cerr << "Error in exit parsing" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
                if(peek().has_value() && peek().value().type == TokenType::semi){
                    consume();
                }else{
                    std::cerr << "Error in parsing, maybe no semicolon?" << std::endl;
                    exit(EXIT_FAILURE);
                }
            } 
            m_index = 0;
            return exit_node;
        }

    private:
        [[nodiscard]] inline std::optional<Token> peek(int ahead = 1) const { 
            if(m_index + ahead > m_tokens.size()){
                return {};
            }else{
                return m_tokens.at(m_index);
            }
        }

        inline Token consume(){
            return m_tokens.at(m_index++);
        }
        const std::vector<Token> m_tokens;
        size_t m_index = 0; // size cause its index 

};