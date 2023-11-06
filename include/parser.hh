#pragma once
#include "apx.hh"
#include "lexer.hh"
#include "ast.hh"

namespace apx{

class Parser{
    public:
        Parser(Lexer lexer) :_lexer(lexer){}
        Ast nodes();
    private:
        Lexer _lexer;
};

};