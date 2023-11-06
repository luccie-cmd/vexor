#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <fmt/core.h>
#include "deps/clopts.hh"
#include "vex.hh"
#include "lexer.hh"
#include "parser.hh"
#include "sema.hh"
#include "ir_gen.hh"

using namespace command_line_options;
using namespace std::literals;

using options = clopts<
    flag<"--print-ast", "Print the AST">,
    positional<"file", "The file whoms contents should be read and compiled", file<>, /*required=*/true>,
    help<>
>;

int main(int argc, char** argv){
    auto opts = options::parse(argc, argv);
    auto file_contents = opts.get<"file">()->contents;
    bool print_ast = opts.get<"--print-ast">();
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
    ir.print();
    return 0;
}