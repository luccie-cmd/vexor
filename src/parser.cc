#include "../include/parser.hh"

vex::Ast vex::Parser::nodes(){
    vex::Ast ret_ast(AstType::ROOT);

    Token tok = _lexer.next_token();
    while(1){
        while(tok.get_type() == TokenType::KEYWORD && tok.get_data() == "var"){
            std::string name = _lexer.expect(TokenType::ID).get_data();
            ret_ast.add_child(AstVarDecl(name));
            Token n = _lexer.next_token();
            if(n.get_type() == TokenType::SEMICOLON){
                tok = _lexer.next_token();
            } else if(n.get_type() == TokenType::EQUAL){
                AstVarAssign assign(name, _lexer.next_token().get_data());
            } else{
                fmt::println("Unexpected token: `{}`", n.get_data());
            }
            _lexer.expect(TokenType::SEMICOLON);
            tok = _lexer.next_token();
        }
        while(tok.get_type() == TokenType::KEYWORD && tok.get_data() == "func"){
            fmt::println("Too lazy to support func decl!");
            while(tok.get_type() != TokenType::CLOSE_CURLY){
                tok = _lexer.next_token();
            }
            tok = _lexer.next_token();
        }
        // tok = _lexer.next_token();
        if(tok.get_type() == TokenType::TT_EOF){
            break;
        } else{
            fmt::print("Invalid token: `{}`\n", tok.get_data());
            std::exit(1);
        }
    }
    return ret_ast;
}