#define _DATA_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Data
{
    private:
        int vertices; //número de vértices
        int numArcos; //número de arcos
        int origem; // indice da origem
        int destino;//indice do escoadouro
        std::vector<double> fluxo_max; //por arco
        std::vector<std::vector<int> > arcos; //por arco
        int n;

        //problema do fluxo de custo minimo
        std::vector<double> demanda; //por arco
        std::vector<double> custo; //por arco
        
        public:
        Data(char* filePath);

        int getVertices();
        int getNumArcos();
        int getOrigem();
        int getDestino();
        double getFluxoMax(int numArcos);
        int getArcos (int numArcos, int n);
        double getDemanda(int numArcos);
        double getCusto (int numArcos);

};