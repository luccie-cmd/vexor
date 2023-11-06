#pragma once
#include <string>
#include <cstdint>
#include <fmt/core.h>

namespace apx{

using usz = uint64_t;

enum struct TokenType{
    KEYWORD,
    ID,
    EQUAL,
    NUMBER,
    SEMICOLON,
    TT_EOF,
};

class Token{
    public:
        Token(TokenType tt, std::string d) :_data(d), _type(tt){}
        void print(){
            fmt::print("`{}` `{}`\n", tt_as_str(_type), _data);
        }
        std::string tt_as_str(TokenType tt){
            switch(tt){
                case apx::TokenType::ID:        return "ID";      break;
                case apx::TokenType::EQUAL:     return "=";       break;
                case apx::TokenType::NUMBER:    return "NUMBER";  break;
                case apx::TokenType::SEMICOLON: return ";";       break;
                case apx::TokenType::TT_EOF:    return "EOF";     break;
            }
            return "";
        }
        TokenType get_type(){ return _type; }
        std::string get_data(){ return _data; }
    private:
        std::string _data;
        apx::TokenType _type;
};

};