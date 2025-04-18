#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() 
{
    IloEnv env;
    try 
    {
        IloModel model(env);

        IloNumVar x_amgs (env, 0.0, IloInfinity, ILOFLOAT, "amgs");
        IloNumVar x_re (env, 0.0, IloInfinity, ILOFLOAT, "re");

        /* 
            Lucro = Valor de venda - Custo de produção
            Lucro = 20 - (5 * 1 + 4 * 1)
        */ 
        IloObjective obj = IloMaximize(env, 11 * x_amgs + 12 * x_re);
        model.add(obj);

        model.add(x_amgs + 4 * x_re <= 10000);
        model.add(5 * x_amgs + 2 * x_re <= 30000);

        IloCplex cplex(model);
        cplex.solve();

        cout << "AMGS: " << cplex.getValue(x_amgs) << " kg" << endl;
        cout << "RE: " << cplex.getValue(x_re) << " kg" << endl;
        cout << "Lucro total: " << cplex.getObjValue() << endl;

    } 
    catch (IloException& e) 
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    
    return 0;
}
