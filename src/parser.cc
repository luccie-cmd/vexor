#include "../include/parser.hh"

vex::Ast vex::Parser::nodes(bool is_body){
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
                ret_ast.add_child(assign);
                _lexer.expect(TokenType::SEMICOLON);
            } else{
                fmt::println("Unexpected token: `{}`", n.get_data());
                std::exit(1);
            }
            tok = _lexer.next_token();
        }
        while(tok.get_type() == TokenType::KEYWORD && tok.get_data() == "func"){
            std::string name = _lexer.expect(TokenType::ID).get_data();
            _lexer.expect(TokenType::OPEN_PAREN);
            Token n = _lexer.next_token();
            if(n.get_type() != TokenType::CLOSE_PAREN){
                fmt::print("Unable to handle function arguments for now!\n");
                std::exit(1);
            }
            _lexer.expect(TokenType::OPEN_CURLY);
            Ast body = nodes(true);
            AstFuncDecl ast(name);
            ast.set_body(body);
            ret_ast.add_child(ast);
            tok = _lexer.next_token();
        }
        if(tok.get_type() == TokenType::TT_EOF || (tok.get_type() == TokenType::CLOSE_CURLY && is_body)){
            break;
        } else{
            // check if it's a statement
            Token n = _lexer.next_token();
            if(n.get_type() == TokenType::OPEN_PAREN){
                AstFuncCall call(tok.get_data());
                n = _lexer.next_token();
                while(n.get_type() != TokenType::CLOSE_PAREN){
                    call.add_arguments(n);
                    n = _lexer.next_token();
                }
                _lexer.expect(TokenType::SEMICOLON);
                ret_ast.add_child(call);
            } else{
                // two checks bc why not
                if(n.get_type() == TokenType::TT_EOF || (n.get_type() == TokenType::CLOSE_CURLY && is_body)) break;
                fmt::print("Invalid token: `{}`\n", tok.get_data());
                fmt::print("Next: `{}`\n", n.get_data());
                std::exit(1);
            }
        }
    }
    return ret_ast;
}