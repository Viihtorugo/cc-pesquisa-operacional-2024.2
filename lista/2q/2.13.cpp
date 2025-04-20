#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main()
{
    IloEnv env;
    try
    {
        IloModel model(env);

        int n = 10;

        vector<pair<int, int>> edges = {
            {0, 1},
            {0, 2},
            {0, 3},
            {1, 3},
            {2, 5},
            {2, 3},
            {5, 6},
            {5, 7},
            {6, 3},
            {6, 9},
            {1, 4},
            {3, 4},
            {9, 7},
            {8, 9},
            {6, 7},
            {3, 6}};

        vector<vector<int>> g(n, vector<int>(n));

        for (auto [u, v] : edges)
        {
            g[u][v] = 1;
            g[v][u] = 1;
        }

        IloNumVarArray x(env, n);

        // Variaveis de decisão
        for (int i = 0; i < n; ++i)
        {
            string var_name = "vertice_" + to_string(i + 1);
            x[i] = IloIntVar(env, 0, 1, var_name.c_str());
        }

        // Função Objetivo
        IloExpr obj(env);

        for (int i = 0; i < n; ++i)
            obj += x[i];

        model.add(IloMaximize(env, obj));

        // Restrições - adicionar os vertices que não são vizinhos
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; ++j)
                if (g[i][j] == 0)
                    model.add(x[i] + x[j] <= 1);

        
        IloCplex cplex(model);
        cplex.solve();

        cout << "Clique maxima: " << cplex.getObjValue() << endl
             << endl;

        cout << "Clique:\n\n";
        for (int i = 0; i < n; i++)
            if (cplex.getValue(x[i]))
                cout << "Vertice " << (i + 1) << endl;
    }
    catch (IloException &e)
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();

    return 0;
}
