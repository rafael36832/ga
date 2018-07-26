#include <iostream>
#include <algorithm>
#include <time.h>
#include <math.h>
#include "values.h"
#define nPop 41

Values data;

class Individuo {

    int * pop;              // population vector
    int no;                 //Number of depots
    int nc;                 //Number of costumers
    int n;                  //Total of depots and constumers

public:

    Individuo(){data.LoadBarreto("../Instances/21x5.dat");

        pop = new int[nPop];    // start population vector with size nPop data.LoadBarreto("../Instances/21x5.dat");

    }

    int fitness(){              // calculate and return the fitness value of i individual
        
        return 0;

    }
    
};    

using namespace std;

int main(){
    
    data.LoadBarreto("../Instances/21x5.dat");
    Individuo pop;data.LoadBarreto("../Instances/21x5.dat");




    

    
    
    return 0;
}