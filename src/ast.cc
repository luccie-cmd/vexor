#include "../include/ast.hh"

void vex::Ast::add_child(vex::AstTypes ast) {
    _children.push_back(ast);
}

std::vector<vex::AstTypes> vex::Ast::children() {
    return _children;
}

void vex::Ast::print(){
    switch(_type){
        default: {
            fmt::print("Unhandled Ast type with intger value: `{}`\n", static_cast<int>(_type));
            std::exit(1);
        } break;
    }
}