#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

void solve ()
{
    IloEnv env;
    try 
    {
        IloModel model(env);

        IloIntVarArray x(env, 6);
        
        for (int i = 0; i < 6; ++i) 
        {
            string var_name = "x" + to_string(i + 1);
            x[i] = IloIntVar(env, 0, IloIntMax, var_name.c_str());
        }

        vector <int> p;
        p.push_back(35);
        p.push_back(30);
        p.push_back(60);
        p.push_back(50);
        p.push_back(27);
        p.push_back(22);

        /* 
            Custo = somatorio (preço * qtd)
        */

        IloExpr obj(env);
        for (int i = 0; i < 6; ++i)
            obj += (x[i] * p[i]);

        model.add(IloMinimize(env, obj));

        // Restrição para Total Vitamina A >= 9
        IloExpr res_a(env);

        vector <int> a;
        a.push_back(1);
        a.push_back(0);
        a.push_back(2);
        a.push_back(2);
        a.push_back(1);
        a.push_back(2);

        for (int i = 0; i < 6; ++i)
            res_a += (x[i] * a[i]);

        model.add(res_a >= 9);

        // Restrição para Total Vitamina C >= 19
        IloExpr res_c(env);

        vector <int> c;
        c.push_back(0);
        c.push_back(1);
        c.push_back(3);
        c.push_back(1);
        c.push_back(3);
        c.push_back(2);

        for (int i = 0; i < 6; ++i)
            res_c += (x[i] * c[i]);

        model.add(res_c >= 19);

        IloCplex cplex(model);
        cplex.solve();

        for (int i = 0; i < 6; ++i)
            cout << "Item " << (i + 1) << ": " << cplex.getValue(x[i]) << endl;

        cout << "Custo mínimo: " << cplex.getObjValue() << endl;

    } 
    catch (IloException& e) 
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
}

int main() 
{
    solve();
            
    return 0;
}
