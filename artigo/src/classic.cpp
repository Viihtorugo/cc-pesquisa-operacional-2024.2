#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main()
{

    IloEnv env;

    try
    {
        // Entrada
        ifstream file_data;
        file_data.open("src/input/data1.txt");

        if (file_data.is_open())
        {
            int n, m;
            file_data >> n >> m;

            cout << "Número de vértices: "<< n << " e número de arestas: " << m << '\n';

            vector<vector<int>> g(n, vector<int>());


            for (int i = 0; i < m; i++)
            {
                int u, v;

                file_data >> u >> v;

                g[u].push_back(v);
                g[v].push_back(u);
            }

            int k;
            file_data >> k;

            vector<double> sig(n, false);

            for (int i = 0; i < k; i++)
            {
                int num;
                file_data >> num;

                sig[num] = true;
            }

            file_data.close();

            IloModel model(env);

            // Variaveis de decisão
            IloNumVarArray x(env, n);

            for (int i = 0; i < n; ++i)
            {
                string var_name = "vertice_" + to_string(i + 1);
                x[i] = IloIntVar(env, 0, 1, var_name.c_str());
            }

            // Função Objetivo
            IloExpr obj(env);

            for (int i = 0; i < n; ++i)
                obj += x[i];

            model.add(IloMinimize(env, obj));


            // Restrições - verificar se os vizinhos foram escolhidos
            for (int i = 0; i < n; i++)
            {
                IloExpr sum(env);
                sum += x[i];

                for (auto v : g[i])
                        sum += x[v];

                model.add(sum >= 1);
            }

            IloCplex cplex(model);
            cplex.solve();

            ofstream file_output;
            file_output.open("src/output/out1.txt");
            
            if (file_output.is_open())
            {
                cout << "Solution status: " << cplex.getStatus() << endl;
                cout << "Tamanho mínimo da cobertura: " << cplex.getObjValue() << endl;
                cout << "Vértices na cobertura: ";

                for (int i = 0; i < n; ++i)
                {
                    if (cplex.getValue(x[i]))
                    {
                        cout << i << " ";
                        file_output << i << '\n';
                    }
                }

                cout << endl;

                file_output.close();
            }
            else
            {
                cout << "Erro ao criar o arquivo ou arquivo não existe!\n";
                exit(1);
            }
        }
        else
        {
            cout << "Erro ao abrir o arquivo ou arquivo não existe!\n";
            exit(1);
        }

        env.end();
    }
    catch (IloException &e)
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    return 0;
}