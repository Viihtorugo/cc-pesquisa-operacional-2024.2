#include <bits/stdc++.h>
#include <ilcplex/ilocplex.h>

using namespace std;

int main() 
{
    IloEnv env;
    try 
    {
        IloModel model(env);

        IloNumVar sol_a_sn (env, 0.0, IloInfinity, ILOFLOAT, "SolASN");
        IloNumVar sol_a_sr (env, 0.0, IloInfinity, ILOFLOAT, "SolASR");
        IloNumVar sol_b_sn (env, 0.0, IloInfinity, ILOFLOAT, "SolBSN"); 
        IloNumVar sol_b_sr (env, 0.0, IloInfinity, ILOFLOAT, "SolBSR");
        IloNumVar sec_sn (env, 0.0, IloInfinity, ILOFLOAT, "SECSN");
        IloNumVar sec_sr (env, 0.0, IloInfinity, ILOFLOAT, "SECSR");
        IloNumVar cor_sn (env, 0.0, IloInfinity, ILOFLOAT, "CORSN");
        IloNumVar cor_sr (env, 0.0, IloInfinity, ILOFLOAT, "CORSR");
        

        /* 
            Custo = somatorio da produção da tinta
        */ 
        IloObjective obj = IloMinimize(env, 1.5 * (sol_a_sn + sol_a_sr) + 1 * (sol_b_sn + sol_b_sr) + 4 * (sec_sn + sec_sr) + 6 * (cor_sn + cor_sr));
        model.add(obj);

        //Quantidade de SEC
        model.add(sec_sn + sol_a_sn * 0.3 + 0.6 * sol_b_sn >= 50);
        model.add(sec_sr + sol_a_sr * 0.3 + 0.6 * sol_b_sr >= 250);

        //Quantidade do COR
        model.add(cor_sn + sol_a_sn * 0.7 + 0.4 * sol_b_sn >= 125);
        model.add(cor_sr + sol_a_sr * 0.7 + 0.4 * sol_b_sr >= 500);
        
        //Total para produzir SR
        model.add(sec_sr + sol_a_sr + sol_b_sr + cor_sr == 1000);
        //Total para produzir SN
        model.add(sec_sn + sol_a_sn + sol_b_sn + cor_sn == 250);

        cout << fixed << setprecision(2);
        IloCplex cplex(model);
        cplex.solve();
        
        double sol_a =  cplex.getValue(sol_a_sn) + cplex.getValue(sol_a_sr);
        double sol_b =  cplex.getValue(sol_b_sn) + cplex.getValue(sol_b_sr);
        double sec =  cplex.getValue(sec_sn) + cplex.getValue(sec_sr);
        double cor =  cplex.getValue(cor_sn) + cplex.getValue(cor_sr);

        cout << "Tinta Secagem Rapida: \n\n";

        double total_sr = cplex.getValue(cor_sr) + cplex.getValue(sol_a_sr) + cplex.getValue(sol_b_sr) + cplex.getValue(sec_sr);
        cout << "Sol A: " << cplex.getValue(sol_a_sr) << endl;
        cout << "Sol B: " << cplex.getValue(sol_b_sr) << endl;
        cout << "  SEC: " << cplex.getValue(sec_sr) << endl;
        cout << "  COR: " << cplex.getValue(cor_sr) << endl << endl;
        cout << "Total: " << total_sr << " litros" <<  endl << endl;

        double total_sn = cplex.getValue(cor_sn) + cplex.getValue(sol_a_sn) + cplex.getValue(sol_b_sn) + cplex.getValue(sec_sn);
        cout << "Tinta Secagem Normal: \n\n";
        cout << "Sol A: " << cplex.getValue(sol_a_sn) << endl;
        cout << "Sol B: " << cplex.getValue(sol_b_sn) << endl;
        cout << "  SEC: " << cplex.getValue(sec_sn) << endl;
        cout << "  COR: " << cplex.getValue(cor_sn) << endl;
        cout << "Total: " << total_sn << " litros" << endl << endl;

        cout << "\n\nQuantidade das variáveis: \n\n";
        cout << "Sol A: " << sol_a << endl;
        cout << "Sol B: " << sol_b << endl;
        cout << "  SEC: " << sec << endl;
        cout << "  COR: " << cor << endl << endl;
        
        cout << "Custo mínimo: " << cplex.getObjValue() << endl;

    } 
    catch (IloException& e) 
    {
        cerr << "Erro: " << e.getMessage() << endl;
    }

    env.end();
    
    return 0;
}
