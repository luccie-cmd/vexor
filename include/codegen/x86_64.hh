#ifndef VEXOR_CODEGEN_X86_64_H
#define VEXOR_CODEGEN_X86_64_H

#include "../vex.hh"
#include "../ir.hh"

namespace vex{
namespace code_gen{

class x86_64{
    public:
        x86_64(IR ir, std::string file) :_ir(ir), out_file(file){}
        void emit_nasm();
        std::string next_ir_inst(IR ir);
    private:
        IR _ir;
        std::string out_file;
};

};
};

#endif