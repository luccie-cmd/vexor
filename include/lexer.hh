#ifndef VEXOR_LEXER_H
#define VEXOR_LEXER_H

#include "vex.hh"

namespace vex{

class Lexer{
    public:
        Lexer(std::string content) :_content(content){
            if(content.size() == 0){
                fmt::print("Cannot lex empty input!\n");
                std::exit(1);
            }
            _current_c = _content.at(0);
            _index = 0;
        }
        Token next_token();
        Token expect(TokenType tt);
    private:
        void advance();
        void skip_whitespace();
        usz _index;
        std::string _content;
        char _current_c;
};

};

#endif