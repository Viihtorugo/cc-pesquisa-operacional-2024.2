#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() 
{
    IloEnv env;
    try 
    {
        IloModel model(env);

        int n = 5, w = 20;
        vector <int> valor = {10, 14, 7, 9, 19};
        vector <int> peso = {11, 13, 7, 5, 13};

        //Variaveis de decisão
        IloNumVarArray x(env, n);

        for (int i = 0; i < n; ++i)
        {
            string var_name = "item_" + to_string(i + 1);
            x[i] = IloIntVar(env, 0, 1, var_name.c_str());
        }
        
        //Função Objetivo
        IloExpr obj(env);
        
        for (int i = 0; i < n; ++i)
            obj += (x[i] * valor[i]);

        model.add(IloMaximize(env, obj));

        //Restrições dos items escolhidos atraves do peso
        IloExpr sum(env);
        for (int i = 0; i < n; i++)
            sum += (x[i] * peso[i]);
        
        model.add(sum <= w);

        IloCplex cplex(model);
        cplex.solve();

        cout << "Melhor valor dos items: " << cplex.getObjValue() << endl << endl;

        for (int i = 0; i < n; i++)
            if (cplex.getValue(x[i]))
                cout << "Item " << (i + 1) << " está na mochila!" << endl;
    } 
    catch (IloException& e) 
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    
    return 0;
}
