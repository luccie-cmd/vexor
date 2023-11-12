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

using namespace command_line_options;

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
    if(print_ast){
        fmt::print("Before SeMa\n");
        nodes.print();
    }
    vex::Sema sema(nodes);
    sema.check();
    nodes = sema.optimize();
    if(print_ast){
        fmt::print("Before SeMa\n");
        nodes.print();
    }
    return 0;
}