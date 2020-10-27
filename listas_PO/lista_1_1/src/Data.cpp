#include "../include/Data.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

Data::Data(char* filePath)
{
    FILE* f = fopen(filePath,"r");

    if(fscanf(f, "%d", &numCulturas) != 1)
    {
        printf("Problem while reading instance.1\n");
        //exit(1);
    }
    

    //lendo limite do armazem 
  
    if(fscanf(f, "%lf", &limiteArm) != 1)
    {
        printf("Problem while reading instance.2\n");
       // exit(1);
    }

    //lendo area cultivavel
  
    if(fscanf(f, "%lf", &areaCultivavel) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }
  

    //lendo produtividade por cultura
    prodCultura = std::vector<double>(numCulturas);
    for(int i = 0; i <numCulturas; i++){

        if(fscanf(f, "%lf", &prodCultura[i]) != 1)
        {
            printf("Problem while reading instance.4\n");
            //exit(1);
        }
    }

    //lendo lucro por cultura
    lucroCultura = std::vector<double>(numCulturas);
    for(int i = 0; i < numCulturas; i++)
    {
        if(fscanf(f, "%lf", &lucroCultura[i]) != 1)
        {
            printf("Problem while reading instance.5\n");
           // exit(1);
        }
    }

    //lendo semanda por cultura
    demandaCultura = std::vector<double>(numCulturas);
    for(int i = 0; i < numCulturas; i++)
    {
        if(fscanf(f, "%lf", &demandaCultura[i]) != 1)
        {
            printf("Problem while reading instance.6\n");
            //exit(1);
        }
    }
    fclose(f);
}

int Data::getNumCulturas()
{
    return numCulturas;
}

double Data::getLimiteArm()
{
    return limiteArm;
}

double Data::getAreaCultivavel()
{
    return areaCultivavel;
}

double Data::getProdCultura(int cultura)
{
    return prodCultura[cultura];
}

double Data::getLucroCultura(int cultura)
{
    return lucroCultura[cultura];
}

double Data::getDemandaCultura(int cultura)
{
    return demandaCultura[cultura];
}
