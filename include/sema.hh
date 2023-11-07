#ifndef VEXOR_SEMA_H
#define VEXOR_SEMA_H

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

#endif