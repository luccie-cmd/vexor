#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <fmt/core.h>
#include "apx.hh"
#include "lexer.hh"
#include "parser.hh"

int main(){
    std::string contents;
    std::ifstream t("./test/main.apx");
    if(!t.is_open()){
        fmt::print("No file or directory named `{}`\n", "./test/main.apx");
    }
    std::stringstream buffer;
    buffer << t.rdbuf();
    contents = buffer.str();

    apx::Lexer lexer(contents);
    apx::Parser parser(lexer);
    parser.nodes().print();
    return 0;
}