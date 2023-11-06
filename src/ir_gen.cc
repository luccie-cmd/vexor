#include "ir_gen.hh"

vex::IR vex::IRGen::generate_ir(){
    IR main_ir("__root__", vex::IRType::FUNCTION);
    for(vex::Ast a : _ast.children()){
        switch(a.get_type()){
            case vex::AstType::ROOT: {
                fmt::print("Fix the faulty sema we got a root in the children\n");
                std::exit(1);
            } break;
            case vex::AstType::VAR_DECL: {
                IR ir("define_var", vex::IRType::INST);
                ir.add_operand(a.operands().at(0));
                main_ir.add_child(ir);
            } break;
            case vex::AstType::VAR_ASSIGN: {
                IR ir("store", vex::IRType::INST);
                ir.add_operand(a.operands().at(0));
                ir.add_operand(a.operands().at(1));
                main_ir.add_child(ir);
            } break;
        }
    }
    IR exit_ir("exit", vex::IRType::INST);
    exit_ir.add_operand(Token(vex::TokenType::NUMBER, "0"));
    main_ir.add_child(exit_ir);
    return main_ir;
}

void vex::IR::print(){
    switch(_type){
        case vex::IRType::FUNCTION: {
            fmt::print("\nIR\n");
            fmt::print("{}:\n", _name);
        } break;
        case vex::IRType::INST: {
            fmt::print("    {}", _name);
            for(Token t : _operands){
                fmt::print(" {}", t.get_data());
            }
            fmt::print("\n");
        } break;
    }
    for(IR i : _children){
        i.print();
    }
}