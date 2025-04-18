#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() 
{
    IloEnv env;
    try 
    {
        IloModel model(env);

        IloNumVar sol_a (env, 0.0, IloInfinity, ILOFLOAT, "SolA");
        IloNumVar sol_b (env, 0.0, IloInfinity, ILOFLOAT, "SolB");
        IloNumVar sec (env, 0.0, IloInfinity, ILOFLOAT, "SEC");
        IloNumVar cor (env, 0.0, IloInfinity, ILOFLOAT, "COR");
        

        /* 
            Lucro = Valor de venda - Custo de produção
            Lucro = 20 - (5 * 1 + 4 * 1) = 11
            Lucro = 30 - (2 * 1 + 4 * 4) = 12
        */ 
        IloObjective obj = IloMinimize(env, 1.5 * sol_a + 1 * sol_b + 4 * sec + 6 * cor);
        model.add(obj);

        model.add(sec + sol_a * 0.3 + 0.6 * sol_b >= 300);
        model.add(cor + sol_a * 0.7 + 0.4 * sol_b >= 625);
        model.add(sec + sol_a + sol_b + cor == 1250);

        cout << fixed << setprecision(2);
        IloCplex cplex(model);
        cplex.solve();

        cout << "Quantidade das variáveis: \n\n";
        cout << "Sol A: " << cplex.getValue(sol_a) << endl;
        cout << "Sol B: " << cplex.getValue(sol_b) << endl;
        cout << "  SEC: " << cplex.getValue(sec) << endl;
        cout << "  COR: " << cplex.getValue(cor) << endl << endl;
        
        cout << "Custo mínimo: " << cplex.getObjValue() << endl;

    } 
    catch (IloException& e) 
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    
    return 0;
}
