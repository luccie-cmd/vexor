#pragma once
#include "vex.hh"
#include <vector>

namespace vex{

enum struct AstType{
    ROOT,
    VAR_DECL,
    VAR_ASSIGN,
};

class Ast{
    public:
        Ast(AstType type){
            _type = type;
        }
        void add_child(Ast ast){
            _children.push_back(ast);
        }
        void add_operand(Token tok){
            _operands.push_back(tok);
        }
        void print(){
            switch(_type){ 
                case AstType::ROOT: {
                    fmt::print("AST\n");
                } break;
                case AstType::VAR_DECL: {
                    fmt::print("|- VAR DECL\n");
                    fmt::print("|   |- NAME: `{}`\n", _operands.at(0).get_data());
                } break;
                case AstType::VAR_ASSIGN: {
                    fmt::print("|- VAR ASSIGN\n");
                    fmt::print("|   |- NAME: `{}`\n", _operands.at(0).get_data());
                    fmt::print("|   |- VALUE: `{}`\n", _operands.at(1).get_data());
                } break;
            }
            for(Ast a : _children){
                a.print();
            }
        }
    private:
        AstType _type;
        std::vector<Ast> _children;
        std::vector<Token> _operands;
};

};