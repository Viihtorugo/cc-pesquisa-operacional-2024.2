#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

vector<vector<int>> floyd_warshall(int n, const vector<vector<int>> &adj_matrix) {
    vector<vector<int>> dist = adj_matrix;
    const int INF = numeric_limits<int>::infinity();

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    return dist;
}

int main() {

    IloEnv env;
    
    try 
    {
        // Entrada
        ifstream file_data;
        
        //file_data.open("src/input/data1.txt");
        file_data.open("src/input/data2.txt");

        int n, m, N = 250;
        file_data >> n >> m;
            
        //vector <pair<int, int>> edges;
        vector <vector <int>> g (n, vector <int> ());
        vector <vector <int>> adj_matrix (n, vector <int> (n));
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
                int u, v, w;

                file_data >> u >> v >> w;

                g[u].push_back(v);
                g[v].push_back(u);
                adj_matrix[u][v] = v;
                adj_matrix[v][u] = w;
            }
        }
        else
        {
            cout << "Erro ao abrir o arquivo ou arquivo não existe!\n";
            exit(1);
        }

        vector <vector <int>> dist = floyd_warshall(n, adj_matrix);

        /*
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << dist[i][j] << " ";
            }

            cout << "\n";
        }
        */

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
                if (dist[i][v] <= N)
                    sum += x[v];

            model.add(sum >= 1);
        }

        // Restringir vértices com grau <= 2
        for (int i = 0; i < n; ++i)
            if (num_streets[i] <= 2)
                model.add(x[i] == 0);
            


        IloCplex cplex(model);
        cplex.solve();

        ofstream file_output;

        //file_output.open("src/output/out1.txt");
        file_output.open("src/output/out2.txt");

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

    } catch (IloException &e) {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    return 0;
}