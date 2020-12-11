

/*



*/


#define _DATA_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
class Data
{
    private:
        int numSemanas; //j
        int numProdutos; //i
        int cc1; // custo c1
        int cc2; // custo c2
        int cf;// custo fixo
        int ep1; // custo estoque de p1
        int ep2; // custo estoque de p2
        int ec1; // custo estoque de c1
        int ec2; // custo estoque de c2
        
        std::vector<int>  demandaSem; //demanda da semana


    public:
        Data(char* filePath);

        int getNumSemanas();

        int getNumProdutos();

        int getCC1();

        int getCC2();

        int getCF();

        int getEP1();

        int getEP2();

        int getEC1();

        int getEC2();

        int getDemandaSemana(int semana);
};
