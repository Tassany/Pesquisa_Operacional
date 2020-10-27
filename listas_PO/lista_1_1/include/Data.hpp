/*
Trigo, Arroz, Milho
i = 1,...,m  número de culturas
produtividade por cultura = ai
lucro por cultura = bi
demanda da aŕea por cultura = ci
área cultivável = d
limite do armazém = e


max => somatório i=1 até n de bi*xi
restrições:
 somatório de i=1 até n de xi/ai <= d
 xi/ai => ci, para todo i
 somatório de i=1 até n de xi <= e
xi>=0 para todo i

*/


#define _DATA_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
class Data
{
    private:
        int numCulturas;
        double limiteArm;
        double areaCultivavel;
        std::vector<double>  prodCultura;
        std::vector<double> lucroCultura;
        std::vector<double>  demandaCultura;

    public:
        Data(char* filePath);

        int getNumCulturas();

        double getLimiteArm();

        double getAreaCultivavel();

        double getProdCultura(int cultura);

        double getLucroCultura(int cultura);

        double getDemandaCultura(int cultura);
};
