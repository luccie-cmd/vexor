#include "../include/sema.hh"
#include <unordered_map>

#define AST_FUNC_DECL 0
#define AST_FUNC_CALL 1
#define AST_VAR_DECL 2
#define AST_VAR_ASSIGN 3

static auto lookup_ast_index(int index){
    return index;
}

void vex::Sema::check(){
    for(vex::AstTypes ast : _ast.children()){
        switch(lookup_ast_index(ast.index())){
            case AST_VAR_DECL: {
                if(std::find(declared_vars.begin(), declared_vars.end(), std::get<AstVarDecl>(ast).get_name()) != declared_vars.end()){
                    fmt::print("Redefinition of already declared function `{}`\n", std::get<AstVarDecl>(ast).get_name());
                    std::exit(1);
                }
                declared_vars.push_back(std::get<AstVarDecl>(ast).get_name());
            } break;
            case AST_VAR_ASSIGN: {
                if(std::find(declared_vars.begin(), declared_vars.end(), std::get<AstVarAssign>(ast).get_name()) == declared_vars.end()){
                    fmt::print("Cannot assign to undeclared variable `{}`\n", std::get<AstVarAssign>(ast).get_name());
                    std::exit(1);
                }
            } break;
            case AST_FUNC_DECL: {
                std::string functionNameToCheck = std::get<AstFuncDecl>(ast).get_name();
                auto foundFunction = std::find_if(
                    declared_func.begin(),
                    declared_func.end(),
                    [functionNameToCheck](const auto& pair) {
                        return pair.first == functionNameToCheck;
                    }
                );

                if (foundFunction != declared_func.end()) {
                    fmt::print("Redefinition of already declared function `{}`\n", functionNameToCheck);
                    std::exit(1);
                }

                declared_func.push_back(std::make_pair(std::get<AstFuncDecl>(ast).get_name(), std::get<AstFuncDecl>(ast).get_arguments().size()));
                vex::Sema sema(std::get<AstFuncDecl>(ast).get_body());
                sema.check();
                std::get<AstFuncDecl>(ast).set_body(sema.optimize());
            } break;
            case AST_FUNC_CALL: {
                called_funcs.push_back(std::make_pair(std::get<AstFuncCall>(ast).get_name(), std::get<AstFuncCall>(ast).get_arguments().size()));
            } break;
        }
    }
}
vex::Ast vex::Sema::optimize(){
    fmt::print("Optimizing isn't implemented\n");
    // std::exit(1);
    return _ast;
}