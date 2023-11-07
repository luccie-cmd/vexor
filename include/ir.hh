#ifndef VEXOR_IR_H
#define VEXOR_IR_H

#include "vex.hh"
#include "ast.hh"

namespace vex{

enum struct MInstType{
    FUNCTION_DECL,
    VAR_DEF,
    VAR_STORE,
    EXIT,
};

class MInst{
    public:
        void add_child(MInst child){ _children.push_back(child); }
        std::vector<MInst> get_children() { return _children; }
        void add_operand(std::string operand){ _operands.push_back(operand); }
        std::vector<std::string> get_operands() { return _operands; }
        void set_type(MInstType type){ _type = type; }
        void emit(){
            switch(_type){
                case MInstType::FUNCTION_DECL: {
                    fmt::print("global {}\n{}:\n", _operands.at(0), _operands.at(0));
                } break;
                case MInstType::VAR_DEF: {
                    fmt::print("; {} is defined in segment .bss\n", _operands.at(0));
                } break;
                case MInstType::VAR_STORE: {
                    // x = 69420;
                    // mov [x], 69420
                    fmt::print("mov [{}], {}\n", _operands.at(0), _operands.at(1));
                } break;
                case MInstType::EXIT: {
                    fmt::print("mov rdi, rax\n");
                    fmt::print("mov rax, 60\n");
                    fmt::print("syscall\n");
                } break;
            }
            for(MInst inst : _children){
                inst.emit();
            }
        }
    private:
        MInstType _type;
        std::vector<MInst> _children;
        std::vector<std::string> _operands;
};

enum struct IRType{
    FUNCTION, // for the _start and user defined functions
    INST,
};

class IR{
    public:
        IR(std::string name, IRType type) :_name(name), _type(type) {}
        void add_operand(vex::Token tok){ _operands.push_back(tok); }
        void add_child(IR ir){ _children.push_back(ir); }
        std::vector<vex::Token> get_operands() { return _operands; }
        std::vector<IR> get_children() { return _children; }
        void set_bit_width(usz bw){ bit_width = bw; }
        IRType get_type() { return _type; }
        usz get_bit_width() { return bit_width; }
        std::string get_name() { return _name; }
        void print();
        // this lowers the current ir to almost machine code to contain the name in _operands[0] and then the last argument at _operands[N]
        MInst lower();
    private:
        std::string _name;  // can be used for the instruction name or the function name
        IRType _type;       // specify if it's a function or an instruction or an ...
        usz bit_width;
        std::vector<vex::Token> _operands;
        std::vector<IR> _children;
};

class IRGen{
    public:
        IRGen(vex::Ast ast) :_ast(ast){}
        IR generate_ir();
    private:
        vex::Ast _ast;
};

};

#endif