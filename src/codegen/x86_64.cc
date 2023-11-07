#include "../../include/codegen/x86_64.hh"
#include <unordered_map>
#include <string>

struct Var{
    std::string bw;
    std::string name;
};

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

std::vector<Var> vars;

std::string vex::code_gen::x86_64::next_ir_inst(IR ir){
    switch(ir.get_type()){
        case vex::IRType::FUNCTION: {
            return fmt::format("\n{}:\n    push rbp\n    mov rbp, rsp\n", ir.get_name());
        } break;
        case vex::IRType::INST: {
            auto inx = insts.find(ir.get_name());
            if(inx != insts.end()){
                auto& instsMap = inx->second;
                for (const auto& [key, value] : instsMap) {
                    InstsEnum instEnum = key;
                    vex::usz num = value;
                    switch(instEnum){
                        case InstsEnum::VAR_DEF:{
                            std::string name = ir.get_operands().at(0).get_data();
                            std::string bw_suffix = "res";
                            switch(ir.get_bit_width()){
                                case 64: bw_suffix += "q"; break;
                                case 32: bw_suffix += "d"; break;
                                case 16: bw_suffix += "w"; break;
                                case 8: bw_suffix += "b"; break;
                            }
                            Var var;
                            var.bw = bw_suffix;
                            var.name = name;
                            vars.push_back(var);
                            return fmt::format("    ; {} is at the end in segment .bss\n", name); 
                        } break;
                        case InstsEnum::VAR_STORE: return fmt::format("    mov {}WORD [{}], {}\n", "Q", ir.get_operands().at(0).get_data(), ir.get_operands().at(1).get_data()); break;
                        case InstsEnum::EXIT: {
                            std::string ret;
                            ret += fmt::format("    cmp al, 0\n    jne .ret\n    xor rax, rax\n.ret:\n");
                            ret += fmt::format("    mov rsp, rbp\n    pop rbp\n    ret\n");
                            return ret;
                        } break;
                    }
                }
            } else{
                std::exit(1);
            }
        } break;
    }
    return "\n";
}

void vex::code_gen::x86_64::emit_nasm(){
    std::string out =   "BITS 64\n"
                        "segment .text\n"
                        "global _start\n"
                        "_start:\n"
                        "    call __root__\n"
                        "    mov rdi, rax\n"
                        "    mov rax, 60\n"
                        "    syscall\n";
    out += next_ir_inst(_ir);
    for(IR ir : _ir.get_children()){
        out += next_ir_inst(ir);
    }
    out += "\nsegment .bss\n";
    for(Var v : vars){
        out += fmt::format("{}: {}\n", v.name, v.bw);
    }
    fmt::print("{}\n", out);
}