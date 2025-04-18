#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() 
{
    IloEnv env;
    try 
    {
        IloModel model(env);

        vector<int> d = {5, 6, 4, 7, 3, 4, 6};
        
        //Variaveis de decisão
        IloNumVarArray x(env, 7);
        for (int i = 0; i < 7; ++i) 
        {
            string var_name = "x_" + to_string(i + 1);
            x[i] = IloIntVar(env, 0, IloIntMax, var_name.c_str());
        }

        //Função Objetivo
        IloExpr obj(env);
        
        for (int i = 0; i < 7; ++i)
            obj += x[i];

        model.add(IloMinimize(env, obj));
        
        //Restrições
        for (int i = 0; i < 7; ++i)
        {
            IloExpr sum(env);

            for (int j = 4; j >= 0; j--)
                sum += x[ ((i - j) + 7) % 7 ];
            
            model.add(sum >= d[i]);
        }

        IloCplex cplex(model);
        cplex.solve();

        cout << "Número mínimo de enfermeira: " << cplex.getObjValue() << endl << endl;

        for (int i = 0; i < 7; ++i)
            cout << cplex.getValue(x[i]) << " enfermeira(s) comeraçaram no dia " << (i + 1) << endl;

    } 
    catch (IloException& e) 
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    
    return 0;
}
