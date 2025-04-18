#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() 
{
    IloEnv env;
    try 
    {
        IloModel model(env);
        
        //Função objetivo
        IloArray<IloNumVarArray> x(env, 3);
        for (int i = 0; i < 3; ++i) {
            x[i] = IloNumVarArray(env, 3);
            for (int j = 0; j < 3; ++j) {
                string var_name = "x_" + to_string(i) + "_" + to_string(j);
                x[i][j] = IloIntVar(env, 0, IloIntMax, var_name.c_str());
            }
        }

        vector<vector<int>> c = {
            {8, 5, 6},
            {15, 10, 12},
            {3, 9, 10}
        };
        
        IloExpr obj(env);

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                obj += (x[i][j] * c[i][j]);

        model.add(IloMinimize(env, obj));
        
        // Restrição das fabricas enviando os produtos
        vector <int> fab;
        fab.push_back(120);
        fab.push_back(80);
        fab.push_back(80);

        for (int i = 0; i < 3; ++i)
        {
            IloExpr sum(env);
            for (int j = 0; j < 3; ++j)
                sum += x[i][j];

            model.add(sum == fab[i]);
        }

        //Restrição da capacidade de cada deposito
        vector <int> dep;
        dep.push_back(150);
        dep.push_back(70);
        dep.push_back(60);

        for (int i = 0; i < 3; ++i)
        {
            IloExpr sum(env);
            for (int j = 0; j < 3; ++j)
                sum += x[j][i];

            model.add(sum == dep[i]);
        }

        IloCplex cplex(model);
        cplex.solve();

        //Verificando o resultado atraves do deposito
        for (int i = 0; i < 3; ++i)
        {
            cout << "Deposito " << i + 1 << ": \n\n";

            int total = 0;

            for(int j = 0; j < 3; ++j)
            {
                total += cplex.getValue(x[j][i]);
                cout << "Recebe " << cplex.getValue(x[j][i]) << " items da Fabrica " << j + 1 << endl;
            }

            cout << "Quantidade nesse deposito: " << total << endl << endl;
        }

        cout << "Custo minimo: " << cplex.getObjValue() << endl;

    } 
    catch (IloException& e) 
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    
    return 0;
}
