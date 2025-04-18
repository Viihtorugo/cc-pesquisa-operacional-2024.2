#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() 
{
    IloEnv env;
    try 
    {
        IloModel model(env);
        
        vector <string> t;
        t.push_back("Milho");
        t.push_back("Arroz");
        t.push_back("Feijão");

        IloArray<IloNumVarArray> x(env, 3);
        for (int i = 0; i < 3; ++i) {
            x[i] = IloNumVarArray(env, 3);
            for (int j = 0; j < 3; ++j) {
                string var_name = "x_fazenda" + to_string(i) + "_" + t[j];
                x[i][j] = IloNumVar(env, 0, IloInfinity, var_name.c_str());
            }
        }

        IloExpr obj(env);
        
        vector <int> l;
        l.push_back(5000);
        l.push_back(4000);
        l.push_back(1800);

        for (int i = 0; i < 3; ++i)
            obj += ((x[i][0] + x[i][1] + x[i][2]) * l[i]);

        model.add(IloMaximize(env, obj));

        //restrição do tamanho da area da fazenda
        vector <double> area_fazenda;
        area_fazenda.push_back(400);
        area_fazenda.push_back(600);
        area_fazenda.push_back(350);

        //restrição da qtd de agua de cada fazenda
        vector <double> total_agua_area;
        total_agua_area.push_back(1800);
        total_agua_area.push_back(2200);
        total_agua_area.push_back(950);

        vector <double> agua_area;
        agua_area.push_back(5.5);
        agua_area.push_back(4);
        agua_area.push_back(3.5);
        

        for (int i = 0; i < 3; ++i)
        {
            model.add(x[i][0] + x[i][1] + x[i][2] <= area_fazenda[i]);
            model.add(agua_area[0] * x[i][0] + agua_area[1] * x[i][1] + agua_area[2] * x[i][2] <= total_agua_area[i]);
        }
        
        //Restrição da area max de cada cultura
        vector <double> area_max;
        area_max.push_back(660);
        area_max.push_back(880);
        area_max.push_back(400);

        for (int i = 0; i < 3; ++i)
            model.add(x[0][i] + x[1][i] + x[2][i] <= area_max[i]);

        IloCplex cplex(model);
        cplex.solve();


    } 
    catch (IloException& e) 
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    
    return 0;
}
