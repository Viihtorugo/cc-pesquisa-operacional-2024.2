#include <ilcplex/ilocplex.h>
#include <iostream>

int main() {
    IloEnv env;
    try {
        std::cout << "CPLEX funcionando com C++!" << std::endl;
    } catch (IloException& e) {
        std::cerr << "Erro: " << e.getMessage() << std::endl;
    }
    env.end();
    return 0;
}
