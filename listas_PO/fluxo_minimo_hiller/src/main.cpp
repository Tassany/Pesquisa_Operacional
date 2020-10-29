#include "../include/Data.hpp"
#include <stdio.h>
#include <iostream>
#include <ilcplex/ilocplex.h>

void solve(Data& data);

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("Usage:\n./tas instance\n");
        return 0;
    }

    Data data(argv[1]);
    solve(data);

    return 0;
}



void solve(Data& data)
{
    IloEnv env;
    IloModel modelo(env);
    //Como a variável depende de i e j é necessário criar um vetor de duas dimensões
    //vector<vector<float>>x seria a criação do vetor normalmente, entretanto o cplex funciona de outra forma
    //Depois de criado o vetor, é preciso preencher cada indice i do array com um vetor de tamanho j

    IloArray <IloNumVarArray> x(env, data.getNumI());
    for(int i = 0; i < data.getNumI(); i++)
    {
        IloNumVarArray vetAux(env, data.getNumJ(), 0, IloInfinity);
    
        x[i] = vetAux;
    }

     //adiciona a variavel x ao modelo
    for(int i = 0; i < data.getNumI(); i++)
    {
        for(int j = 0; j < data.getNumJ(); j++){
            char name[100];
            sprintf(name, "X(%d)(%d)", i,j);
            x[i][j].setName(name);
            modelo.add(x[i][j]);
        }
    }

    //Criando a Função Objetivo  
    IloExpr obj(env);
    for(int i = 0; i < data.getNumI(); i++)
    {
        for(int j = 0; j < data.getNumJ(); j++){
            obj+=data.getCusto(i,j)*x[i][j];
        }
    }
    // Adicionando a FO
    modelo.add(IloMinimize(env, obj));


    //Restricoes

    IloExpr nos(env);
    for(int i = 0; i < data.getNumI(); i++){
        IloExpr somaEntrada(env);
        IloExpr somaSaida(env);
        for(int j = 0; j < data.getNumJ(); j++){
            
            somaEntrada += (x[i][j]);
        }
        for(int j = 0; j < data.getNumJ(); j++){

            somaSaida+= (x[j][i]);
        }
        nos = somaSaida - somaEntrada;

        modelo.add( (nos == data.getFluxoLiq(i)));
    }

    for(int i = 0; i < data.getNumI(); i++){
        for(int j = 0; j < data.getNumJ(); j++){
        
    
            modelo.add(x[i][j] <= data.getCapacidadeMax(i,j));  
        }
       
    }

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
    std::cout << "custo minimo:" << tas.getObjValue() << std::endl;
    

}