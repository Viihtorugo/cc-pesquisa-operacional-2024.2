#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() {

    IloEnv env;
    
    try 
    {
        // Entrada
        ifstream file_data;
        
        //file_data.open("src/input/data1.txt");
        file_data.open("src/input/data2.txt");

        int n, m;
        file_data >> n >> m;
            
        //vector <pair<int, int>> edges;
        vector <vector <int>> g (n, vector <int> ());
        vector <int> num_streets;
        
        if (file_data.is_open()) 
        {

            for (int i = 0; i < n; i++)
            {
                int num;
                file_data >> num;
                num_streets.push_back(num);
            }

            for (int i = 0; i < m; i++)
            {
                int u, v;

                file_data >> u >> v;

                g[u].push_back(v);
                g[v].push_back(u);
                cout << "index: " << i << endl;
            }
        }
        else
        {
            cout << "Erro ao abrir o arquivo ou arquivo não existe!\n";
            exit(1);
        }
        IloModel model(env);

        //Variaveis de decisão

        IloNumVarArray x(env, n);

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

        // Restringir vértices com grau <= 2
        for (int i = 0; i < n; ++i)
        {
            if (num_streets[i] <= 2)
            {
                model.add(x[i] == 0);
            }
        }


        IloCplex cplex(model);
        cplex.solve();

        ofstream file_output;

        //file_output.open("src/output/out1.txt");
        file_output.open("src/output/out2.txt");

        if (file_output.is_open()) 
        {
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

    } catch (IloException &e) {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    return 0;
}