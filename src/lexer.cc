#include "lexer.hh"
#include <vector>
#include <algorithm>
#include <cctype>

static std::vector<apx::Token> single_tokens = {
    apx::Token(apx::TokenType::EQUAL, "="),
    apx::Token(apx::TokenType::SEMICOLON, ";"),
};

apx::Token apx::Lexer::next_token(){
    skip_whitespace();
    if(_index >= _content.size()){
        return Token(TokenType::TT_EOF, "\0");
    }
    skip_whitespace();

    skip_whitespace();
    for(Token t : single_tokens){
        if(*t.get_data().c_str() == _current_c){
            advance();
            return t;
        }
    }
    skip_whitespace();

    skip_whitespace();
    if(isalnum(_current_c)){
        std::string data;
        data.push_back(_current_c);
        while(isalnum(_current_c)){
            advance();
            data.push_back(_current_c);
        }
        data.pop_back();
        if(data.empty()){
            fmt::print("Lexer failed!\n");
            std::exit(1);
        }
        if(isdigit(data.at(0))){
            return Token(TokenType::NUMBER, data);
        }
        return Token(TokenType::ID, data);
    }
    skip_whitespace();

    fmt::print("Invalid character found starting with: `{}`\n", _current_c);
    fmt::print("This should return an invalid token eventually\n");
    std::exit(1);
}

apx::Token apx::Lexer::expect(apx::TokenType tt){
    apx::Token ret = next_token();
    if(ret.get_type() != tt){
        fmt::print("Expected token type `{}` but got `{}` with value `{}`\n", ret.tt_as_str(tt), ret.tt_as_str(ret.get_type()), ret.get_data());
        std::exit(1);
    }
    return ret;
}

void apx::Lexer::advance(){
    if(_index < _content.size()-1){
        _index++;
        _current_c = _content.at(_index);
    }
}

void apx::Lexer::skip_whitespace(){
    while((isblank(_current_c) || _current_c == '\n') && _index < _content.size()-1){
        advance();
    }
}