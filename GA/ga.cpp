#include <iostream>
#include <algorithm>
#include <time.h>
#include <math.h>
#include "values.h"
#define nPop 41

Values data;

class Individuo {

public:
    
    int * pop;              // population vector
    int fitnessValue = 0; 
    bool possible = true;
    int carroNow = 0; 
    int depotNow = pop[0];
    int depotNowValue = 0;
    int wayNow = pop[0];

    Individuo(){

        pop = new int[nPop];    // start population vector with size nPop data.LoadBarreto("../Instances/21x5.dat");

    }

    int fitness(){              // calculate and return the fitness value of i individual
        
        fitnessValue += data.FV;

        for(int i=1; i<data.N; i++){
            
            
            if(pop[i] == 0){    // zero 
                
                // aux

                wayNow = depotNow;
                carroNow = 0;

                // fitness 

                fitnessValue += data.FV; 


            } else if(pop[i] < data.No){ // it's a depot

                if (wayNow < data.No) {

                    depotNow = pop[i]; 
                    wayNow = pop[i];

                } else { 
                    
                    fitnessValue += data.FD[depotNow];

                    wayNow = pop[i];
                    depotNow = pop[i]; 
                    
                }

            } else {                // it's a costumerar

                if(data.CD[depotNow] >= (depotNowValue + data.d[pop[i]])){ // verificar se o depot pode 
                    
                    if(data.CV >= (carroNow + data.d[pop[i]])){ // verificar se o carro pode

                        depotNowValue += data.d[pop[i]];    
                        fitnessValue += data.c[wayNow][pop[i]]; 
                        carroNow +=  data.d[pop[i]];
                        wayNow = pop[i];

                    } else {  // o carro não pode
                        
                        depotNowValue += data.d[pop[i]];
                        fitnessValue += data.c[depotNow][pop[i]];
                        carroNow =  data.d[pop[i]];
                        wayNow = pop[i];

                        fitnessValue += data.FV;

                    }                             
            
            
                }  else { // impossível

                    possible = false;

                }
        }

    }
    
};    

using namespace std;

int main(){
    
    data.LoadBarreto("../Instances/21x5.dat");
    Individuo pop;data.LoadBarreto("../Instances/21x5.dat");


    
    return 0;
}