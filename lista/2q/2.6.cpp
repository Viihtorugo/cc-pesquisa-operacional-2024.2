#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main()
{

    IloEnv env;

    try
    {
        IloModel model(env);

        // Vertices de verificação

        /*
        int s = 0, t = 3;
        vector <vector <int>> cap = {
            {0, 10, 5, 0},
            {0, 0, 15, 8},
            {0, 0, 0, 10},
            {0, 0, 0, 0}
        }; */

        int s = 1, t = 6;
        vector <vector <int>> cap = {
            //  0  1   2   3   4   5   6
            /*0*/ {0, 0, 0, 0, 0, 0, 0},
            /*1*/ {0, 0, 16, 13, 0, 0, 0},
            /*2*/ {0, 0, 0, 10, 12, 0, 0},
            /*3*/ {0, 0, 0, 0, 0, 14, 0},
            /*4*/ {0, 0, 0, 9, 0, 0, 20},
            /*5*/ {0, 0, 0, 0, 7, 0, 4},
            /*6*/ {0, 0, 0, 0, 0, 0, 0}
            };

        int n = cap.size();

        // Variaveis de decisões
        IloArray<IloNumVarArray> x(env, n);
        for (int i = 0; i < n; ++i)
        {
            x[i] = IloNumVarArray(env, n);
            for (int j = 0; j < n; ++j)
            {
                if (cap[i][j] > 0)
                    x[i][j] = IloIntVar(env, 0, cap[i][j]);
                else
                    x[i][j] = IloIntVar(env, 0, 0); // fluxo impossível
            }
        }

        // Função objetivo: maximizar o fluxo
        IloExpr total(env);
        for (int j = 0; j < n; ++j)
            total += x[s][j];

        // Restrição - Somatorio da saida == Somatorio da entrada
        for (int v = 0; v < n; ++v)
        {
            if (v == s || v == t)
                continue;

            IloExpr in(env), out(env);
            for (int i = 0; i < n; ++i)
                in += x[i][v];
            for (int j = 0; j < n; ++j)
                out += x[v][j];

            model.add(in == out);
        }

        model.add(IloMaximize(env, total));

        IloCplex cplex(model);
        cplex.solve();

        // Verificando a saída
        cout << "Fluxo máximo: " << cplex.getObjValue() << endl;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (cap[i][j] > 0)
                    cout << "Fluxo de " << i << " para " << j << ": " << cplex.getValue(x[i][j]) << endl;
    }
    catch (IloException &e)
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();

    return 0;
}