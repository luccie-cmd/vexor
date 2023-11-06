#include "parser.hh"

apx::Ast apx::Parser::nodes(){
    apx::Ast ret_ast(apx::AstType::ROOT);
    apx::Token tok = _lexer.next_token();
    while(tok.get_type() == apx::TokenType::KEYWORD){
        if(tok.get_data() == "var"){
            apx::Token name = _lexer.expect(apx::TokenType::ID);
            apx::Ast ast(apx::AstType::VAR_DECL);
            ast.add_operand(name);
            ret_ast.add_child(ast);
            tok = _lexer.next_token();
            if(tok.get_type() == apx::TokenType::EQUAL){
                apx::Ast assign(apx::AstType::VAR_ASSIGN);
                assign.add_operand(name);
                assign.add_operand(_lexer.next_token());
                ret_ast.add_child(assign);
            }
        }
        _lexer.expect(apx::TokenType::SEMICOLON);
        tok = _lexer.next_token();
    }
    _lexer.expect(apx::TokenType::SEMICOLON);
    return ret_ast;
}