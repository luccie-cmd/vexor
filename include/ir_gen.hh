#pragma once
#include "vex.hh"
#include "ast.hh"

namespace vex{

enum struct IRType{
    FUNCTION, // for the __root__ and user defined functions
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
    private:
        std::string _name; // can be used for the instruction name or the function name
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