#include "../include/Data.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

Data::Data(char* filePath)
{
    FILE* f = fopen(filePath, "r");

    if(!f)
    {
        printf("Problem while reading instance 1.\n");
        exit(1);
    }

    //lendo o numero de nós que entra e os que saem
    if(fscanf(f, "%d %d", &numI, &numJ) != 2)
    {
        printf("Problem while reading instance.2\n");
        exit(1);
    }


    //lendo o custo de acordo com a matrix de vetores dos nós que saem e os que entram
    custo = std::vector<std::vector<double> >(numI, std::vector<double>(numJ));
    for(int i = 0; i < numI; i++)
    {
        for(int j = 0; j < numJ; j++)
        {
            if(fscanf(f, "%lf", &custo[i][j]) != 1)
            {
                printf("Problem while reading instance.3\n");
                exit(1);
            }
        }
    }


    //lendo a capacidade máxima de acordo com a matrix de vetores dos nós que saem e os que entram
    capacidadeMax = std::vector<std::vector<double> >(numI, std::vector<double>(numJ));
    for(int i = 0; i < numI; i++)
    {
        for(int j = 0; j < numJ; j++)
        {
            if(fscanf(f, "%lf", &capacidadeMax[i][j]) != 1)
            {
                printf("Problem while reading instance.4\n");
                exit(1);
            }
        }
    }

    //lendo a capacidade minima de acordo com a matrix de vetores dos nós que saem e os que entram
    capacidadeMin = std::vector<std::vector<double> >(numI, std::vector<double>(numJ));
    for(int i = 0; i < numI; i++)
    {
        for(int j = 0; j < numJ; j++)
        {
            if(fscanf(f, "%lf", &capacidadeMin[i][j]) != 1)
            {
                printf("Problem while reading instance.5\n");
                exit(1);
            }
        }
    }

    //lendo o fluxo líquido de cada nó
    fluxoLiq = std::vector<float>(numI);
    for(int i = 0; i <numI; i++)
    {
        if(fscanf(f, "%lf", &fluxoLiq[i]) != 1)
        {
            printf("Problem while reading instance.6\n");
            exit(1);
        }
    }

    fclose(f);
}


int Data::getNumI()
{
    return numI;
}

int Data::getNumJ()
{
    return numJ;
}

double Data::getCusto(int I, int J)
{
    return custo[I][J];
}

double Data::getCapacidadeMax(int I, int J)
{
    return capacidadeMax[I][J];
}

double Data::getCapacidadeMin(int I, int J)
{
    return capacidadeMin[I][J];
}

float Data::getFluxoLiq(int I)
{
    return fluxoLiq[I];
}