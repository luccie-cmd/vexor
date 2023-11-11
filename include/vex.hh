#ifndef VEXOR_VEX_H
#define VEXOR_VEX_H

#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <fmt/core.h>

namespace vex{

using usz = uint64_t;

enum struct TokenType{
    KEYWORD,
    ID,
    STRING_LITERAL,
    EQUAL,
    PLUS,
    MINUS,
    NUMBER,
    SEMICOLON,
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_CURLY,
    CLOSE_CURLY,
    DOT,
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
                case vex::TokenType::KEYWORD:        return "KEYWORD"; break;
                case vex::TokenType::STRING_LITERAL: return "STRING";  break;
                case vex::TokenType::ID:             return "ID";      break;
                case vex::TokenType::EQUAL:          return "=";       break;
                case vex::TokenType::PLUS:           return "+";       break;
                case vex::TokenType::MINUS:          return "-";       break;
                case vex::TokenType::NUMBER:         return "NUMBER";  break;
                case vex::TokenType::SEMICOLON:      return ";";       break;
                case vex::TokenType::OPEN_PAREN:     return "(";       break;
                case vex::TokenType::CLOSE_PAREN:    return ")";       break;
                case vex::TokenType::OPEN_CURLY:     return "{";       break;
                case vex::TokenType::CLOSE_CURLY:    return "}";       break;
                case vex::TokenType::DOT:            return ".";       break;
                case vex::TokenType::TT_EOF:         return "EOF";     break;
            }
            return "";
        }
        TokenType get_type(){ return _type; }
        std::string get_data(){ return _data; }
    private:
        std::string _data;
        vex::TokenType _type;
};

};

#endif