#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <fmt/core.h>
#include "vex.hh"
#include "lexer.hh"
#include "parser.hh"

int main(){
    std::string contents;
    std::ifstream t("./test/main.vex");
    if(!t.is_open()){
        fmt::print("No file or directory named `{}`\n", "./test/main.vex");
    }
    std::stringstream buffer;
    buffer << t.rdbuf();
    contents = buffer.str();

    vex::Lexer lexer(contents);
    vex::Parser parser(lexer);
    parser.nodes().print();
    return 0;
}