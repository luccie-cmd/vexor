#include "lexer.hh"
#include <vector>

apx::Token apx::Lexer::next_token(){
    skip_whitespace();
    if(_index >= _content.size()-1){
        return Token(TokenType::TT_EOF, 0);
    }

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

    fmt::print("Invalid character found starting with: `{}`\n", _current_c);
    fmt::print("This should return an invalid token eventually\n");
    std::exit(1);
}

void apx::Lexer::advance(){
    if(_index < _content.size()-1){
        _index++;
        _current_c = _content.at(_index);
    }
}

void apx::Lexer::skip_whitespace(){
    while((_current_c == ' ' || _current_c == '\t' || _current_c == '\n' || _current_c == '\r') && _index < _content.size()-1){
        advance();
    }
}