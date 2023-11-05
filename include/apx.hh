#pragma once
#include <string>
#include <fmt/core.h>

namespace apx{

using usz = uint64_t;

enum struct TokenType{
    KEYWORD,
    ID,
    EQUAL,
    NUMBER,
    TT_EOF
};

class Token{
    public:
        Token(TokenType tt, std::string d) :_data(d), _type(tt){}
        void print(){
            // fmt::print("`{}`\n", data);
        }
    private:
        std::string _data;
        apx::TokenType _type;
};
};