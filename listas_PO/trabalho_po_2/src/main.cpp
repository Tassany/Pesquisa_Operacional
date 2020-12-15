#include "../include/Data.hpp"
#include <stdio.h>
#include <iostream>
#include <ilcplex/ilocplex.h>


void solve(Data& data);

int main(int argc, char** argv)
{
    if(argc != 2) // precisa de duas coisas para compilar o programa, o nome do arquivo e as instâncias utilizadas
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

    //variavel  booleana c_j {0,1} que indica se houve compra ou não na semana especifica
    IloBoolVarArray c(env, data.getNumSemanas());
   
    //adiciona a variavel c_j ao modelo
    for(int j = 0; j < data.getNumSemanas(); j++)
    {
        char name[100];
        sprintf(name, "C(%d)", j+1);
        c[j].setName(name);
        modelo.add(c[j]);
    }

    //varivel inteira x_ij = representa a quantidade do produto i na semana j
    IloArray <IloNumVarArray> x(env, data.getNumProdutos());
    for(int i = 0; i < data.getNumProdutos(); i++)
    {
        IloNumVarArray vetor(env, data.getNumSemanas(), 0, IloInfinity, ILOINT);
        x[i] = vetor;
    }

    //adiciona a variavel x_ij ao modelo
    for(int i = 0; i < data.getNumProdutos(); i++)
    {
        for(int j = 0; j < data.getNumSemanas(); j++)
        {
            char name[100];
            sprintf(name, "X(%d,%d)", i+1,j+1);
            x[i][j].setName(name);
            modelo.add(x[i][j]);
        }
    }

    //varivel inteira y_ij = representa a quantidade em estoque do produto i na semana j
    IloArray <IloNumVarArray> y(env, data.getNumProdutos());
    for(int i = 0; i < data.getNumProdutos(); i++)
    {
        IloNumVarArray vetor(env, data.getNumSemanas(), 0, IloInfinity, ILOINT);
        y[i] = vetor;
    }

    //adiciona a variavel y_ij ao modelo
    for(int i = 0; i < data.getNumProdutos(); i++)
    {
        for(int j = 0; j < data.getNumSemanas(); j++)
        {
            char name[100];
            sprintf(name, "Y(%d,%d)", i+1,j+1);
            y[i][j].setName(name);
            modelo.add(y[i][j]);
        }
    }


    ////////////////////////////////////////////
    //Criando a Função Objetivo (FO) 
    IloExpr obj(env);
    for(int j = 0; j < data.getNumSemanas(); j++)
    {
        obj += ((data.getCC1())*x[2][j] + (data.getCC2())*x[3][j] + (data.getEP1())*y[0][j] + (data.getEP2())*y[1][j] + (data.getEC1())*y[2][j] + (data.getEC2())*y[3][j] + data.getCF()*c[j]);
    }
    modelo.add(IloMinimize(env, obj));

    ///////////////////////
    //Restricoes

    /*ESTOQUES NA SEMANA 0*/
    for(int i = 0; i < 1; i++)
    {
        IloRange r = (y[0][0] - x[0][0] + data.getDemandaSemana(0) == 0);
        char name[100];
        sprintf(name, "Estoque_semana_1_produto_1");
        r.setName(name);
        modelo.add(r);

        //modelo.add(y[0][0] == x[0][0] - data.getDemandaSemana(0));
    }

    for(int i = 0; i < 1; i++)
    {
        IloRange r (y[1][0] - x[1][0] + 2*x[0][0] == 0);
        char name[100];
        sprintf(name, "Estoque_semana_1_produto_2");
        r.setName(name);
        modelo.add(r);

        //modelo.add(y[1][0] == x[1][0] - 2*x[0][0]);
    }
    
    for(int i = 0; i < 1; i++)
    {
        IloRange r = (y[2][0] - x[2][0] + 3*x[0][0] + x[1][0] == 0);
        char name[100];
        sprintf(name, "Estoque_semana_1_produto_3");
        r.setName(name);
        modelo.add(r);

        //modelo.add(y[2][0] == x[2][0] - 3*x[0][0] - 2*x[1][0]);
    }

    for(int i = 0; i < 1; i++)
    {
        IloRange r = (y[3][0] - x[3][0] + 2*x[1][0] == 0);
        char name[100];
        sprintf(name, "Estoque_semana_1_produto_4");
        r.setName(name);
        modelo.add(r);

        //modelo.add(y[3][0] == x[3][0] - 4*x[1][0]);
    }
    

    /*ESTOQUES NAS DEMAIS SEMANAS*/
    for(int j = 1; j < data.getNumSemanas(); j++)
    {
        IloRange r = (y[0][j] - y[0][j-1] - x[0][j] + data.getDemandaSemana(j) == 0);
        char name[100];
        sprintf(name, "Estoque_produto_1(%d)", j+1);
        r.setName(name);
        modelo.add(r);
        
        //modelo.add(y[0][j] ==  y[0][j-1] + x[0][j] - data.getDemandaSemana(j));
    }

    for(int j = 1; j < data.getNumSemanas(); j++)
    {
        IloRange r = (y[1][j] - y[1][j-1] - x[1][j] + 2*x[0][j] == 0);
        char name[100];
        sprintf(name, "Estoque_produto_2(%d)", j+1);
        r.setName(name);
        modelo.add(r);

        //modelo.add(y[1][j] ==  y[1][j-1] + x[1][j] - 2*x[0][j]);
    }

    for(int j = 1; j < data.getNumSemanas(); j++)
    {
        IloRange r = (y[2][j] - y[2][j-1] - x[2][j] + 3*x[0][j] + x[1][j] == 0);
        char name[100];
        sprintf(name, "Estoque_produto_3(%d)", j+1);
        r.setName(name);
        modelo.add(r);

        //modelo.add(y[2][j] ==  y[2][j-1] + x[2][j] - 3*x[0][j] - 2*x[1][j]);
    }

    for(int j = 1; j < data.getNumSemanas(); j++)
    {
        IloRange r = (y[3][j] - y[3][j-1] - x[3][j] + 2*x[1][j] == 0);
        char name[100];
        sprintf(name, "Estoque_produto_4(%d)", j+1);
        r.setName(name);
        modelo.add(r);

        //modelo.add(y[3][j] ==  y[3][j-1] + x[3][j] - 4*x[1][j]);
    }


    /*COMPRA INICIAL*/
    for(int i = 0; i < 1; i++)
    {
        IloRange r = (c[0] - 1 == 0);
        char name[100];
        sprintf(name, "Compra_inicial");
        r.setName(name);
        modelo.add(r);

        //modelo.add(c[0] == 1);
    }


    /*COMPRAS*/
    for(int j = 1; j < data.getNumSemanas(); j++)
    {
        IloRange r = (x[2][j] + x[3][j] - (9*(data.getDemandaSemana(j))*c[j]) <= 0);
        char name[100];
        sprintf(name, " Compra_semana(%d)", j+1);
        r.setName(name);
        modelo.add(r);

        //modelo.add(x[2][j] + x[3][j] <= (9*(data.getDemandaSemana(j))*c[j]));
    }


    /*TEMPO MAXIMO*/
    for(int j = 0; j < data.getNumSemanas(); j++)
    {
        IloRange r = (x[0][j] + x[1][j] - 800 <= 0);
        char name[100];
        sprintf(name, "Tempo_maximo(%d)", j+1);
        r.setName(name);
        modelo.add(r);

        //modelo.add((x[0][j] + x[1][j] ) <= 800);
    }


    /*DEMANDAS PELO PRODUTO 1 NAS SEMANAS*/
    for(int j = 0; j < data.getNumSemanas(); j++)
    {
        IloRange r = (x[0][j] - data.getDemandaSemana(j) >= 0);
        char name[100];
        sprintf(name, "Demanda(%d)", j+1);
        r.setName(name);
        modelo.add(r);

        //modelo.add(x[0][j] >= data.getDemandaSemana(j));
    }

    

    IloCplex tas(modelo);
    tas.setParam(IloCplex::TiLim, 2*60*60);
    tas.setParam(IloCplex::Threads, 1);
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
    std::cout << "custo mínimo obtido:" << tas.getObjValue() << std::endl;

    /*o objetivo é decidir para as T semanas o quanto vai ser produzido
    de p1 e p2 e quanto vai ser comprado de c1 e c2

    Lembrando que:
    p1 = 2p2 + 3c1
    p2 = c1 + 2c2
    */

    for(int j = 0; j < data.getNumSemanas(); j++) 
    {
        printf("Quantidade de p1 produzida na semana %d: ", j+1);
        std::cout << tas.getValue(x[0][j]) << std::endl;

        printf("Quantidade de p2 produzida na semana %d: ", j+1);
        std::cout << tas.getValue(x[1][j]) << std::endl;

        printf("Quantidade de c1 comprados na semana %d: ", j+1);
        std::cout << tas.getValue(x[2][j]) << std::endl;

        printf("Quantidade de c2 comprados na semana %d: ", j+1);
        std::cout << tas.getValue(x[3][j]) << std::endl;
    

        printf("Houve compra na semana %d? ", j+1);
        if(tas.getValue(c[j]) == 1){
               std::cout << "sim" << std::endl;
        }else{
            std::cout << "não" << std::endl;
        }
     
        puts("");
    }
}

