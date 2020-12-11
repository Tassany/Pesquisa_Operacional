#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/Data.hpp"

Data::Data(char* filePath)
{
    FILE* f = fopen(filePath,"r");

   

    if(fscanf(f, "%d", &vertices) != 1)
    {
        printf("Problem while reading instance.1\n");
        //exit(1);
    }
    printf("%d",vertices);

    if(fscanf(f, "%d", &numArcos) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }
    numArcos += 1; // adicionou o arco de Origem para o Destino

    if(fscanf(f, "%d", &origem) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }

        if(fscanf(f, "%d", &destino) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }

    //lendo as instancias de cada arco, quais nós chegam e quais saem e seu fluxo maximo
    fluxo_max = std::vector<double>(numArcos);
    n = 2; // nó que vai [0]; nó que chega [1]
    arcos = std::vector<std::vector<int> >(numArcos, std::vector<int>(n));
    for(int i = 0; i < numArcos-1; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(fscanf(f, "%d", &arcos[i][j]) != 1)
            {
                printf("Problem while reading instance.5\n");
                exit(1);
            }

        }

        if(fscanf(f, "%lf", &fluxo_max[i]) != 1)
        {
            printf("Problem while reading instance.5\n");
            exit(1);
        }
    }

    //transformação para o PFCM    
    arcos[numArcos-1][0] = origem;
    arcos[numArcos-1][1] = destino;
    fluxo_max[numArcos-1] = 999999999999.0;

    double fluxo_total_origem = 0.0;
    double fluxo_total_destino = 0.0;
    for(int j = 0; j < numArcos-1; j++)
    {    
        if(arcos[j][0] == origem) //checando se o arco sai da origem
        {
            fluxo_total_origem += fluxo_max[j]; //soma os fluxos
        }

        if(arcos[j][1] == destino) //checando se o arco sai do destino
        {
            fluxo_total_destino += fluxo_max[j]; //soma os fluxos
        }
    }

    double menor = 0.0;
    if(fluxo_total_origem <= fluxo_total_destino)
    {
        menor = fluxo_total_origem;
    }
    else
    {
        menor = fluxo_total_destino;
    }
    

    //Criando demandas
    demanda = std::vector<double>(vertices);

    for(int i = 0; i < vertices; i++)
    {
        if(i+1 == origem)
        {
            demanda[i] = -menor;
            continue;
        }

        if(i+1 == destino)
        {
            demanda[i] = menor;
            continue;
        }

        demanda[i] = 0.0;
    }

    //Criando custos
    custo = std::vector<double>(numArcos);
    for(int j = 0; j < numArcos; j++)
    {
        if(arcos[j][0] == origem && arcos[j][1] == destino) // checa se eh o arco extra criado
        {
            custo[j] = 1.0;
            continue;
        }

        custo[j] = 0.0;
    }

    fclose(f);
}


int Data::getVertices()
{
    return vertices;
}

int Data::getNumArcos()
{
    return numArcos;
}

int Data::getOrigem()
{
    return origem;
}

int Data::getDestino()
{
    return destino;
}

double Data::getFluxoMax(int numArcos)
{
    return fluxo_max[numArcos];
}

int Data::getArcos (int numArcos,int n)
{
    return arcos[numArcos][n];
}

double Data::getDemanda(int numArcos)
{
    return demanda[numArcos];
}

double Data::getCusto (int numArcos){
    return custo[numArcos];
}