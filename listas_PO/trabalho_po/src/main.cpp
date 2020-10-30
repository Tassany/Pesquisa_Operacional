#include <stdio.h>
#include <iostream>
#include <ilcplex/ilocplex.h>
#include "../include/Data.hpp"


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

void solve(Data& data)
{
    IloEnv env;
    IloModel modelo(env);
    IloNumVarArray x(env, data.getNumArcos(), 0, IloInfinity);
    

    //adiciona a variavel x ao modelo
    for(int i = 0; i < data.getNumArcos(); i++)
    {
        char name[100];
        sprintf(name, "X(%d)", i);
        x[i].setName(name);
        modelo.add(x[i]);
    }
    IloExpr obj(env);
    for(int i = 0; i<data.getNumArcos(); i++){
        obj += data.getCusto(i)*x[i];
    }
    
    modelo.add(IloMinimize(env,obj));



    //restrição
  
    for(int i = 0; i < data.getVertices(); i++){
        IloExpr somaEntrada(env);
        IloExpr somaSaida(env);

        for(int j =0 ; j < data.getNumArcos() ; j++){
            for(int n = 0; n < 2; n ++){
                if(data.getArcos(j,n)== i + 1){
                    if(n == 0) //nó que sai
                    {
                        somaSaida += x[j];
                    }
                    else //nó que entra
                    {
                        somaEntrada += x[j];
                    }  
                }
            }
        }

        modelo.add( -somaSaida + somaEntrada == data.getDemanda(i));

    }


    for(int i = 0; i < data.getNumArcos(); i++){

        modelo.add(x[i] <= data.getFluxoMax(i));  
        
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
    double menor = 0.0;

    if(data.getDemanda(data.getOrigem() - 1) <= data.getDemanda(data.getDestino() - 1)){
        menor = -1*data.getDemanda(data.getOrigem() - 1);
    }else{
        menor = data.getDemanda(data.getDestino() - 1);
    }
    double fluxo = menor - tas.getObjValue();
    std::cout << "fluxo máximo:" << fluxo <<  std::endl;


    for(int i = 0; i < data.getNumArcos(); i++) 
    {
        double value = tas.getValue(x[i]);
        if(value > 0.00001)
        {   

            std::cout << "arco " << i + 1 << ": "<<std::endl;

            if(data.getArcos(i,0) ){
                std::cout << "  vai de " << data.getArcos(i,0);
            }
            if(data.getArcos(i,1)){
                std::cout << " até " << data.getArcos(i,1) << std::endl;
            }

            std::cout << " encaminhando " << value << std::endl;
            std::cout << "  " << std::endl;
        }
    }
    

}