#if !defined(VEXOR_SEMA_HH)
#define VEXOR_SEMA_HH
#include "vex.hh"
#include "ast.hh"
#include <utility>

namespace vex{

class Sema{
    public:
        Sema(Ast ast) :_ast(ast) {
            declared_func = {
                {"write", 1}
            };
        }
        void check();
        void find_declared_function(std::pair<std::string, int> d);
        Ast optimize();

    private:
        Ast _ast;
        std::vector<std::string> declared_vars;
        std::vector<std::pair<std::string, int>> declared_func;
        std::vector<std::pair<std::string, int>> called_funcs;
};

};


#endif // VEXOR_SEMA_HH
