#include "../include/ast.hh"
#include <unordered_map>

void vex::Ast::add_child(vex::AstTypes ast) {
    _children.push_back(ast);
}

std::vector<vex::AstTypes> vex::Ast::children() {
    return _children;
}

void vex::Ast::print(std::string prefix){
    switch(_type){
        case AstType::ROOT: {
            fmt::print("{}AST\n", prefix);
        } break;
        default: {
            fmt::print("Unhandled Ast type with intger value: `{}`\n", static_cast<int>(_type));
            std::exit(1);
        } break;
    }
    for(int i = 0; i < _children.size(); ++i){
        AstTypes a = _children.at(i);
        try{
            AstFuncDecl ast = std::get<AstFuncDecl>(a);
            fmt::print("{}FUNC DECL\n", prefix);
            fmt::print("{}|- NAME: {}\n", prefix, ast.get_name());
            fmt::print("{}|- ARGS\n", prefix);
            for(Token t : ast.get_arguments()){
                fmt::print("{}        |- `{}`\n", prefix, t.get_data());
            }
            fmt::print("{}|- BODY\n", prefix);
            ast.get_body().print("|   ");
        } catch(std::bad_variant_access){
            try{
                AstFuncCall ast = std::get<AstFuncCall>(a);
                fmt::print("{}FUNC CALL\n", prefix);
                fmt::print("{}|- NAME: \n", prefix, ast.get_name());
                fmt::print("{}|- ARGS\n", prefix);
                for(Token t : ast.get_arguments()){
                    fmt::print("{}    |- `{}`\n", prefix, t.get_data());
                }
            } catch(std::bad_variant_access){
                try{
                    AstVarAssign ast = std::get<AstVarAssign>(a);
                    fmt::print("{}VAR ASSIGN\n", prefix);
                    fmt::print("{}|- NAME: `{}`\n", prefix, ast.get_name());
                    fmt::print("{}|- VALUE: `{}`\n", prefix, std::get<std::string>(ast.get_value()));
                } catch(std::bad_variant_access){
                    try{
                        AstVarDecl ast = std::get<AstVarDecl>(a);
                        fmt::print("{}VAR DECL\n", prefix);
                        fmt::print("{}|- NAME: `{}`\n", prefix, ast.get_name());
                    } catch(std::bad_variant_access){
                        fmt::print("Error: unsuported Ast type that was implemented\n");
                        fmt::print("Please revert back to the original thanks\n");
                        std::exit(1);
                    }
                }
            }
        }
    }
}