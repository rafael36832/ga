#include <iostream>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "values.h"
#include "dependences.h"
#define nPop 1024
#define nRand 100000
#define nCross 256

class randomico{
public:
    
    randomico(int * aleatorio){      

        srand(time(0));
            
        for(int i=0; i<nRand; i++){

            aleatorio[i] = rand();

        } 

    }

    int next(int * aleatorio, int z){
        
        if(z >= nRand-1)
            z = 0;

        z++;    

        return aleatorio[z];    


    }
};

class Individuo {

public:
    
    int * pop;         // pindividual vector
    double fitnessValue; 
    bool possible;      

};
