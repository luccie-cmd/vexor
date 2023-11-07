#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <fmt/core.h>
#include "../include/deps/clopts.hh"
#include "../include/vex.hh"
#include "../include/lexer.hh"
#include "../include/parser.hh"
#include "../include/sema.hh"
#include "../include/ir_gen.hh"
#include "../include/codegen/x86_64.hh"

using namespace command_line_options;
using namespace std::literals;

using options = clopts<
    flag<"--print-ast", "Print the AST">,
    flag<"--print-ir", "Print the IR">,
    positional<"file", "The file whoms contents should be read and compiled", file<>, /*required=*/true>,
    help<>
>;

int main(int argc, char** argv){
    auto opts = options::parse(argc, argv);
    auto file_contents = opts.get<"file">()->contents;
    bool print_ast = opts.get<"--print-ast">();
    bool print_ir = opts.get<"--print-ir">();
    vex::Lexer lexer(file_contents);
    vex::Parser parser(lexer);
    vex::Ast nodes = parser.nodes();
    vex::Sema sema(nodes);
    std::string ret = sema.check_ast();
    if(ret != "none"){
        fmt::print("Encountered an error\n");
        fmt::print("{}\n", ret);
        std::exit(1);
    }
    if(print_ast){
        nodes.print();
    }
    vex::IRGen irgen(nodes);
    vex::IR ir = irgen.generate_ir();
    if(print_ir){
        ir.print();
    }
    vex::code_gen::x86_64 cdgx86_64(ir, "./out.txt");
    cdgx86_64.emit_nasm();
    return 0;
}