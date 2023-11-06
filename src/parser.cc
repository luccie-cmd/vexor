#include "parser.hh"

vex::Ast vex::Parser::nodes(){
    vex::Ast ret_ast(vex::AstType::ROOT);
    vex::Token tok = _lexer.next_token();
    while(tok.get_type() == vex::TokenType::KEYWORD){
        if(tok.get_data() == "var"){
            vex::Token name = _lexer.expect(vex::TokenType::ID);
            vex::Ast ast(vex::AstType::VAR_DECL);
            ast.add_operand(name);
            ret_ast.add_child(ast);
            tok = _lexer.next_token();
            if(tok.get_type() == vex::TokenType::EQUAL){
                vex::Ast assign(vex::AstType::VAR_ASSIGN);
                assign.add_operand(name);
                assign.add_operand(_lexer.next_token());
                ret_ast.add_child(assign);
            }
        }
        _lexer.expect(vex::TokenType::SEMICOLON);
        tok = _lexer.next_token();
    }
    _lexer.expect(vex::TokenType::SEMICOLON);
    return ret_ast;
}