#pragma once
#include "../vex.hh"
#include "../ir_gen.hh"

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