#ifndef VEXOR_AST_H
#define VEXOR_AST_H

#include "vex.hh"
#include "lexer.hh"
#include <vector>
#include <variant>

namespace vex {

class Ast;
class AstFuncDecl;
class AstFuncCall;
class AstVarDecl;
class AstVarAssign;

// TODO: Mabye support Binary Operators

enum struct AstType {
    NONE,
    ROOT,
    VAR_DECL,
    VAR_ASSIGN,
    FUNC_DECL,
    FUNC_CALL,
};

using AstTypes = std::variant<AstFuncDecl, AstFuncCall, AstVarDecl, AstVarAssign>;

class Ast {
public:
    Ast(AstType type=AstType::NONE) : _type(type) {}
    void add_child(AstTypes ast);
    std::vector<AstTypes> children();
    AstType get_type() { return _type; }
    void print();

private:
    AstType _type;
    std::vector<AstTypes> _children;
};

class AstFuncDecl : public Ast {
public:
    AstFuncDecl(std::string name) :Ast(AstType::FUNC_DECL), _name(name) {}
private:
    std::string _name;
    std::vector<Token> _arguments;
    Ast _body;
};

class AstFuncCall : public Ast {
public:
private:
    int n;
};

class AstVarDecl : public Ast {
public:
    AstVarDecl(std::string name) :Ast(AstType::VAR_DECL), _name(name) {}
private:
    std::string _name;
};

class AstVarAssign : public Ast {
public:
    AstVarAssign(std::string name, std::variant<std::string, int> value) :Ast(AstType::VAR_ASSIGN), _name(name), _value(value){}
private:
    std::string _name;
    std::variant<std::string, int> _value;
};

} // namespace vex

#endif // VEXOR_AST_H
