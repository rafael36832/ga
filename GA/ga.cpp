#include <iostream>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "values.h"
#define nPop 40

Values data;

using namespace std;

class Individuo {

public:
    
    int * pop;              // population vector
    int aux;
    int tam;
    float fitnessValue; 
    bool possible;
    int carroNow; 
    int depotNow;
    int depotNowValue;
    int wayNow;

    Individuo(){
        
        vector<int> RDepot;         
        vector<int> R;
        vector<int>::iterator itR;

       

        for(int i=0; i<data.No; i++){
            
            RDepot.push_back(i);
            R.push_back(i);
            
        }

        for(int i=data.No; i<data.N; i++){
            
            R.push_back(i);
            
        }

        int soma=0; 

        for(int i=data.No; i<data.N; i++){
            
            soma += data.d[i];

        }

        tam = soma / data.CV;

        for(int i=0; i<tam; i++){

            R.push_back(-1);

        }

        pop = new int[data.N + tam];    // start population vector with size nPop data.LoadBarreto("../Instances/21x5.dat");

        // ramdom inicialization
        srand(time(0));
        aux = rand() % data.No;  
        pop[0] = RDepot[aux];
        
        for(itR=R.begin(); itR!=R.end(); itR++){

            if(*itR == RDepot[aux]){

                R.erase(itR);
                break;
            }    

        }
        
        for(int i=1; i<data.N + tam; i++){
            
            srand(time(0));
            aux = rand() % R.size();  
            pop[i] = R[aux];
            
            for(itR=R.begin(); itR!=R.end(); itR++){

                if(*itR == R[aux]){

                    R.erase(itR);
                    break;
                }    

            }

        }

    }

    int fitness(){              // calculate and return the fitness value of i individual
        
        aux = 0;
        tam = 0;
        fitnessValue = 0;
        carroNow = 0;
        depotNow = pop[0];
        wayNow = pop[0];
        depotNowValue = 0;
        possible = true;

        fitnessValue += data.FV;
        possible = true;

        for(int i=1; i<(data.N + tam); i++){
            
            if(pop[i] == -1){    // zero on article, -1 here
                
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

            } else {                // it's a costumer

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
            
            
                }  else { // impossible

                    depotNowValue += data.d[pop[i]];
                    fitnessValue += data.c[depotNow][pop[i]];
                    carroNow =  data.d[pop[i]];
                    wayNow = pop[i];

                    fitnessValue += data.FV;

                    possible = false;

                }
            }

            if(i == data.N + tam - 1){  // last iteration

                if(depotNow != wayNow){ // last depot is opened

                    fitnessValue += data.FD[depotNow];
                    
                }

            }
        }
    
        return fitnessValue;

    }

    void mutation(){

        srand(time(0));

        int randomN1 = (rand() % data.N + tam) + 1;       
        int randomN2 = (rand() % data.N + tam) + 1;

        int aux = pop[randomN1]; 
        pop[randomN1] = pop[randomN2];
        pop[randomN2] = aux; 
        this->fitness();    
    }

    void print(){
        
        for(int i=0; i<(data.N + tam); i++){

            cout << pop[i] << " ";

        } 

        cout << "Fitness: " << fitnessValue << endl;

    }
        
    
};    

int main(){
    
    data.LoadBarreto("../Instances/21x5.dat");
    data.ShowValues();
    Individuo * pop = new Individuo[5];
    for(int i=0; i<5; i++){
        pop[i].fitness();
        pop[i].print();
        pop[i].mutation();
        pop[i].print();
    }    

    return 0;
}
