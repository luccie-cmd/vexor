#pragma once
#include "vex.hh"
#include "ast.hh"

namespace vex{

class Sema{
    public:
        Sema(Ast ast) :_ast(ast){}
        std::string check_ast();
    private:
        Ast _ast;
};

};