#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main()
{
    IloEnv env;
    try
    {
        IloModel model(env);
        
        IloNumVarArray x(env, 4);

        for (int i = 0; i < 4; ++i)
        {
            string var_name = "folha_" + to_string(i + 1);
            x[i] = IloIntVar(env, 0, IloIntMax, var_name.c_str());
        }

        //Restrição quantidade pelo tamanho
        model.add(x[0] + x[2] + x[3] == 200); // tam 1
        model.add(x[1] == 90); // tam 2


        //Restrição para quantidade de latas
        vector <int> copos = {1, 2, 0, 4};
        vector <int> tampas = {7, 3, 9, 4};

        IloExpr lata_copos(env);
        IloExpr lata_tampas(env);
        
        for (int i = 0; i < 4; ++i)
        {
            lata_copos += (x[i] * copos[i]);
            lata_tampas += (x[i] * tampas[i]);
        }

        model.add(2 * lata_copos <= lata_tampas); 

        //Pegar o minimo das variaveis
        IloIntVar latas(env, 0, IloIntMax, "latas");
        model.add(latas <= lata_copos);
        model.add(latas <= lata_tampas);

        IloObjective obj = IloMaximize(env, 50 * latas - 50 * (latas - lata_copos) -  3 * (lata_tampas - 2 * latas));
        model.add(obj);

        IloCplex cplex(model);
        cplex.solve();

        cout << "Lucro total: " << cplex.getObjValue() << endl << endl;
        cout << "Quantidade de latinhas: " << cplex.getValue(latas) << " unidades" << endl;
        cout << "Quantidade de copos: " << cplex.getValue(lata_copos) << " unidades" << endl;
        cout << "Quantidade de tampas: " << cplex.getValue(lata_tampas) << " unidades" << endl << endl;

        cout << "Quantidade de impressão de cada padrão:\n\n";

        for (int i = 0; i < 4; ++i)
            cout << "Quantidade - Folha tipo " << (i + 1) << ": " << cplex.getValue(x[i]) << endl;
        
    }
    catch (IloException &e)
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();

    return 0;
}
