#include "../include/ir.hh"
#include <unordered_map>

vex::IR vex::IRGen::generate_ir(){
    IR main_ir("_start", vex::IRType::FUNCTION);
    for(vex::Ast a : _ast.children()){
        switch(a.get_type()){
            case vex::AstType::ROOT: {
                fmt::print("Fix the faulty sema we got a root in the children\n");
                std::exit(1);
            } break;
            case vex::AstType::VAR_DECL: {
                IR ir("define_var", vex::IRType::INST);
                ir.add_operand(a.operands().at(0));
                ir.set_bit_width(64);
                main_ir.add_child(ir);
            } break;
            case vex::AstType::VAR_ASSIGN: {
                IR ir("store_var", vex::IRType::INST);
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

enum struct InstsEnum{
    VAR_DEF,
    VAR_STORE,
    EXIT,
};
//                  IR name                        codegen inst   ops
std::unordered_map<std::string, std::unordered_map<InstsEnum, vex::usz>> insts = {
    {"define_var", {{InstsEnum::VAR_DEF, 2}}},
    {"store_var", {{InstsEnum::VAR_STORE, 2}}},
    {"exit", {{InstsEnum::EXIT, 1}}},
};

vex::MInst vex::IR::lower(){
    vex::MInst ret;
    switch(_type){
        case vex::IRType::FUNCTION: {
            ret.add_operand(fmt::format("{}", _name));
            ret.set_type(MInstType::FUNCTION_DECL);
        } break;
        case vex::IRType::INST: {
            auto inx = insts.find(_name);
            if(inx != insts.end()){
                auto& instsMap = inx->second;
                for (const auto& [key, value] : instsMap) {
                    InstsEnum instEnum = key;
                    vex::usz num = value;
                    switch(instEnum){
                        case InstsEnum::VAR_DEF: {
                            ret.set_type(MInstType::VAR_DEF);
                            ret.add_operand(fmt::format("{}", this->get_operands().at(0).get_data()));
                        } break;
                        case InstsEnum::VAR_STORE: {
                            ret.set_type(MInstType::VAR_STORE);
                            ret.add_operand(fmt::format("{}", this->get_operands().at(0).get_data()));
                            ret.add_operand(fmt::format("{}", this->get_operands().at(1).get_data()));
                        } break;
                        case InstsEnum::EXIT: {
                            ret.set_type(MInstType::EXIT);
                        } break;
                    }
                }
            }
        } break;
    }
    for(IR i : _children){
        ret.add_child(i.lower());
    }
    return ret;
}