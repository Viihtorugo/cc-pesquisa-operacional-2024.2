#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main()
{
    IloEnv env;
    try
    {
        IloModel model(env);

        /*
        int n = 9;
        vector<vector<int>> g(n, vector<int>());

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
        */

        //grafo completo 4 vert
        int n = 5;
        vector<vector<int>> g(n, vector<int>());
        
        g[0].push_back(1);
        g[1].push_back(0);

        g[0].push_back(2);
        g[2].push_back(0);

        g[0].push_back(3);
        g[3].push_back(0);

        g[0].push_back(4);
        g[4].push_back(0);

        g[1].push_back(2);
        g[2].push_back(1);

        g[1].push_back(3);
        g[3].push_back(1);

        g[1].push_back(4);
        g[4].push_back(1);

        g[2].push_back(3);
        g[3].push_back(2);

        g[2].push_back(4);
        g[4].push_back(2);

        g[3].push_back(4);
        g[4].push_back(3);

        IloNumVarArray x(env, n);

        // Variaveis de decisão
        for (int i = 0; i < n; ++i)
        {
            string var_name = "vertice_" + to_string(i + 1);
            x[i] = IloIntVar(env, 1, IloIntMax, var_name.c_str());
        }

        // Função Objetivo
        IloIntVar obj(env, 0, IloIntMax, "obj");

        // pegar o maior valor
        for (int i = 0; i < n; ++i)
        {
            model.add(obj >= x[i]);
        }

        model.add(IloMinimize(env, obj));

        // Restrições
        for (int i = 0; i < n; ++i)
            for (auto v : g[i])
                model.add(x[i] != x[v]);

        IloCplex cplex(model);
        cplex.solve();

        cout << "Número minimo de frequências: " << cplex.getObjValue() << endl
             << endl;

        cout << "Cores dos vertices:\n";
        for (int i = 0; i < n; ++i)
        {
            cout << "Vertice " << (i + 1) << " - Cor " << cplex.getValue(x[i]) << endl;
        }
    }
    catch (IloException &e)
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();

    return 0;
}
