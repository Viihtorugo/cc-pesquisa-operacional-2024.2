#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() 
{
    IloEnv env;
    try 
    {
        IloModel model(env);

        int n = 9, m = 11;
        vector <vector <int>> g (n, vector <int> ());

        g[0].push_back(1);
        g[1].push_back(0);
        g[0].push_back(2);
        g[2].push_back(0);
        g[0].push_back(3);
        g[3].push_back(0);
        g[0].push_back(7);
        g[7].push_back(0);
        g[1].push_back(3);
        g[3].push_back(1);
        g[2].push_back(3);
        g[3].push_back(2);
        g[3].push_back(4);
        g[4].push_back(3);
        g[3].push_back(5);
        g[5].push_back(3);
        g[3].push_back(6);
        g[6].push_back(3);
        g[6].push_back(7);
        g[7].push_back(6);
        g[5].push_back(8);
        g[8].push_back(5);

        IloNumVarArray x(env, n);
        
        //Variaveis de decisão
        for (int i = 0; i < n; ++i)
        {
            string var_name = "vertice_" + to_string(i + 1);
            x[i] = IloIntVar(env, 0, 1, var_name.c_str());
        }
        
        //Função Objetivo
        IloExpr obj(env);
        
        for (int i = 0; i < n; ++i)
            obj += x[i];

        model.add(IloMinimize(env, obj));

        //Restrições - verificar se os vizinhos foram escolhidos
        for (int i = 0; i < n; i++)
        {
            IloExpr sum(env);
            sum += x[i];

            for (auto v: g[i])
                sum += x[v];
            
            model.add(sum >= 1);
        }

        IloCplex cplex(model);
        cplex.solve();

        cout << "Quantidade de bairros escolhidos: " << cplex.getObjValue() << endl << endl;

        for (int i = 0; i < n; i++)
            if (cplex.getValue(x[i]))
                cout << "Construa no bairro " << (i + 1) << endl;
    } 
    catch (IloException& e) 
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    
    return 0;
}
