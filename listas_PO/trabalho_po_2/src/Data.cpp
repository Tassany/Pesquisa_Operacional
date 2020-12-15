#include "../include/Data.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

Data::Data(char* filePath)
{
    FILE* f = fopen(filePath,"r");

    //lendo o número de semanas
    if(fscanf(f, "%d", &numSemanas) != 1)
    {
        printf("Problem while reading instance.1\n");
        //exit(1);
    }
    

    /* lendo a quantidade de produtos ( ou i)
        como o próprio problema já apresenta 4 produtos específicos, pode-se ler direto
        p1,p2,c1,c2.
    */
    numProdutos = 4;  
    
    
    //lendo custo de c1
    if(fscanf(f, "%d", &cc1) != 1)
    {
        printf("Problem while reading instance.2\n");
       // exit(1);
    }

   
    //lendo custo de c2
    if(fscanf(f, "%d", &cc2) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }
  

    //lendo custo fixo
    if(fscanf(f, "%d", &cf) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }

    //lendo custo de estoque de p1
    if(fscanf(f, "%d", &ep1) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }

    //lendo custo de estoque de p2
    if(fscanf(f, "%d", &ep2) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }

    //lendo custo de estoque de c1
    if(fscanf(f, "%d", &ec1) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }

    //lendo custo de estoque de c2
    if(fscanf(f, "%d", &ec2) != 1)
    {
        printf("Problem while reading instance.3\n");
       // exit(1);
    }

    //lendo demanda da semana
    demandaSem = std::vector<int>(numSemanas);
    for(int i = 0; i <numSemanas; i++){

        if(fscanf(f, "%d", &demandaSem[i]) != 1)
        {
            printf("Problem while reading instance.4\n");
            //exit(1);
        }
    }


    fclose(f);
}

int Data::getNumSemanas()
{
    return numSemanas;
}

int Data::getNumProdutos()
{
    return numProdutos;
}

int Data::getCC1()
{
    return cc1;
}


int Data::getCC2()
{
    return cc2;
}

int Data::getCF()
{
    return cf;
}

int Data::getEP1()
{
    return ep1;
}

int Data::getEP2()
{
    return ep2;
}

int Data::getEC1()
{
    return ec1;
}

int Data::getEC2()
{
    return ec2;
}

int Data::getDemandaSemana(int semana)
{
    return demandaSem[semana];
}
