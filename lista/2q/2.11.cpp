#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main()
{
    IloEnv env;
    try
    {
        IloModel model(env);

        // Custo fixo de instalação
        vector<int> f = {100, 150, 120};

        // Custo de atendimento c[i][j]
        /*
        vector<vector<int>> c = {
            {20, 24, 11, 25},
            {28, 27, 82, 83},
            {74, 97, 71, 96}};
        */

        vector<vector<int>> c = {
            {20, 104, 11, 325},
            {28, 104, 325, 8},
            {325, 5, 5, 96}};

        int n = c.size(), m = c[0].size();

        // Variaveis de decisão
        IloArray<IloBoolVarArray> x(env, n);

        for (int i = 0; i < n; ++i)
            x[i] = IloBoolVarArray(env, m);

        IloBoolVarArray y(env, n);

        // Ativação do deposito
        for (int i = 0; i < n; ++i)
            y[i] = IloBoolVar(env);

        // Função objetivo
        IloExpr obj(env);
        for (int i = 0; i < n; ++i)
        {
            obj += f[i] * y[i];
            for (int j = 0; j < m; ++j)
                obj += c[i][j] * x[i][j];
        }

        model.add(IloMinimize(env, obj));

        // Restrições
        for (int j = 0; j < m; ++j)
        {
            IloExpr sum(env);
            for (int i = 0; i < n; ++i)
                sum += x[i][j];
            model.add(sum == 1);
        }

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                model.add(x[i][j] <= y[i]);

        IloCplex cplex(model);
        cplex.solve();

        cout << "Custo mínimo: " << cplex.getObjValue() << endl
             << endl;

        for (int i = 0; i < n; ++i)
        {
            cout << "Estação " << (i + 1);
            if (cplex.getValue(y[i]))
            {
                cout << " está instalado! Atende os cliente(s): ";

                for (int j = 0; j < m; ++j)
                {
                    if (cplex.getValue(x[i][j]))
                        cout << (j + 1) << " ";
                }

            }
            else
            {
                cout << " não está instalado!\n";
            }

            cout << endl;
        }
    }
    catch (IloException &e)
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();

    return 0;
}
