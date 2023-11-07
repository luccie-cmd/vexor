#include "../include/sema.hh"
#include <algorithm>

std::string vex::Sema::check_ast(){
    if(_ast.get_type() != vex::AstType::ROOT){
        return "Something went wrong in the parser";
    }
    std::vector<std::string> vars;
    for(Ast a : _ast.children()){
        switch(a.get_type()){
            case vex::AstType::ROOT: {
                return "Cannot have 2 roots (faulty parser)";
            } break;
            case vex::AstType::VAR_ASSIGN: {
                if(vars.size() == 0){
                    return  "No variables defined!";
                }
                if (std::find(vars.begin(), vars.end(), a.operands().at(0).get_data()) == vars.end()) 
                    return fmt::format("Variable `{}` not defined!", a.operands().at(0).get_data());
                // the 0th element is already checked in the parser ./src/parser.cc:8
                if(a.operands().at(1).get_type() != vex::TokenType::NUMBER) return "Can only assign number to a variable\n";
            } break;
            case vex::AstType::VAR_DECL: {
                if(a.operands().size() != 1) return "Not enough arguments provided for a variable decleration";
                vars.push_back(a.operands().at(0).get_data());
            } break;
        }
    }
    return "none";
}