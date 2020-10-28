/*
i = nó que vai
j = nó que chega
cij = custo por fluxo entre i e j
uij= capacidade máxima para o arco i e j
lij = capacidade minima para o arco i e j
bi = fluxo líquido gerado no nó i
 n = quantidade de nós
xi = fluxo através do arco i -> j

o custo total deu 480
*/

#define _DATA_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
class Data
{
    private:
        int numI;
        int numJ;
        std::vector<std::vector<double> > custo;
        std::vector<std::vector<double> > capacidadeMax;
        std::vector<std::vector<double> > capacidadeMin;
        std::vector<double> fluxoLiq;

    public:
        Data(char* filePath);  
        int getNumI();
        int getNumJ();
        double getCusto(int I, int J);
        double getCapacidadeMax(int I, int J);
        double getCapacidadeMin(int I, int J);
        double getFluxoLiq(int I);


};



