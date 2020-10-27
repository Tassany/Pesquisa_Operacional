#include "../include/Data.hpp"
#include <stdio.h>
#include <iostream>
#include <ilcplex/ilocplex.h>


void solve(Data& data);

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("Usage:\n./bin instance\n");
        return 0;
    }

    Data data(argv[1]);
    solve(data);

    return 0;
}


void solve(Data& data){
    IloEnv env;
    IloModel modelo(env);

    IloNumVarArray x(env, data.getNumCulturas(), 0, IloInfinity);



    //adiciona a variavel x ao modelo
    for(int i = 0; i < data.getNumCulturas(); i++)
    {
        char name[100];
        sprintf(name, "X(%d)", i);
        x[i].setName(name);
        modelo.add(x[i]);
    }

//Criando a Função Objetivo (FO) 
    IloExpr obj(env);
    for(int i = 0; i < data.getNumCulturas(); i++)
    {
        obj += data.getLucroCultura(i)*x[i];
    }

    modelo.add(IloMaximize(env, obj));


    //Restricoes

    for(int i = 0; i < data.getNumCulturas(); i++) {
       modelo.add( (x[i]/data.getProdCultura(i)) >= data.getDemandaCultura(i));
    }

    IloExpr somaArea(env);
    for(int i = 0; i < data.getNumCulturas(); i++){
        somaArea += (x[i]/data.getProdCultura(i));
    }

    modelo.add((somaArea <= data.getAreaCultivavel()));

   IloExpr somaArm(env);
    for(int i = 0; i < data.getNumCulturas(); i++){
        somaArm += (x[i]);
    }

    modelo.add((somaArm <= data.getLimiteArm()));

    IloCplex tas(modelo);
        tas.setParam(IloCplex::TiLim, 2*60*60);
        tas.setParam(IloCplex::Threads, 1);
    //    tas.setParam(IloCplex::Param::MIP::Interval, 1);
    //    tas.setParam(IloCplex::Param::MIP::Display, 5);
        tas.exportModel("modelo.lp");

        try
        {
            tas.solve();
        }
        catch(IloException& e)
        {
            std::cout << e;
        }


std::cout << "\nstatus:" << tas.getStatus() << std::endl;
    std::cout << "lucro maximo obtido:" << tas.getObjValue() << std::endl;
    
    for(int i = 0; i < data.getNumCulturas(); i++) 
    {

        printf("Produção da cultura %d: ", i+1);
        std::cout << tas.getValue(x[i]) << std::endl;
        
    }
}


