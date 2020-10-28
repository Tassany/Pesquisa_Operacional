#include "Data.hpp"
#include <stdio.h>
#include <iostream>
#include <ilcplex/ilocplex.h>

void solve(Data& data);


{
    if(argc != 2)
    {
        printf("Usage:\n./tas instance\n");
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

    IloNumVarArray x(env, data.getNumI(), 0, IloInfinity);
}