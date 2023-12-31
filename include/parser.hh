#ifndef VEXOR_PARSER_H
#define VEXOR_PARSER_H

#include "vex.hh"
#include "lexer.hh"
#include "ast.hh"

namespace vex{

class Parser{
    public:
        Parser(Lexer lexer) :_lexer(lexer){}
        Ast nodes(bool is_body=false);
    private:
        Lexer _lexer;
};

};

#endif