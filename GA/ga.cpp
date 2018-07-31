#include <iostream>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "values.h"
#define nPop 40
#define nRand 350
#define nCross 20

Values data;
int tam;
int z;
int aleatorio[nRand];

using namespace std;

class randomico{
public:
    
    randomico(){      

        srand(time(0));
            
        for(int i=0; i<nRand; i++){

            aleatorio[i] = rand();

        } 

    }

    int next(){
        
        if(z >= nRand-1)
            z = 0;
        z++;    
        return aleatorio[z];
        

    }
};

randomico r;

class Individuo {

public:
    
    int * pop;              // pindividual vector
    int aux;
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

        aux = r.next() % data.No;  
        pop[0] = RDepot[aux];
        
        for(itR=R.begin(); itR!=R.end(); itR++){

            if(*itR == RDepot[aux]){

                R.erase(itR);
                break;
            }    

        }
        
        for(int i=1; i<data.N + tam; i++){
            
            srand(time(0));
            aux = r.next() % R.size();  
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
                    depotNowValue = 0;
                    wayNow = pop[i];

                } else { 
                    
                    fitnessValue += data.FD[depotNow];

                    wayNow = pop[i];
                    depotNowValue = 0;
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

        int randomN1;
        int randomN2;

        randomN1 = (r.next() % data.N + tam) + 1;       
        randomN2 = (r.next() % data.N + tam) + 1;

        aux = pop[randomN1]; 
        pop[randomN1] = pop[randomN2];
        pop[randomN2] = aux; 
        this->fitness();    
    }

    void print(){
        
        for(int i=0; i<(data.N + tam); i++){

            cout << pop[i] << " ";

        } 

        cout << "Fitness: " << fitnessValue <<" Possivel: " << possible  << endl;

    }
        
    
};

void crossOver1(Individuo * pop){

        int indN1, indN2, random1, random2;
        vector<int> aux;
        vector<int> RDepot;         
        vector<int> R;
        vector<int>::iterator itR;

        for(int j=0; j<nCross; j++){

            indN1 = (r.next() % (nPop/2));       
            indN2 = (r.next() % (nPop/2));
            random1 = (r.next() % (data.N + tam));
            random2 = (r.next() % (data.N + tam));

            if(random1 == 0) 
                random1++;
            if(random2 == 0) 
                random2++;               

            // mesclar pop[indN1] com pop[indN2] a partir do nodo random1

            for(int i=0; i<data.N; i++){
                
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

            for(int i=0; i<random1; i++){
                
                pop[indN1 + (nPop/2)].pop[i] = pop[indN1].pop[i];
                // colocar num vector o que ja tem (ou tirar dum vector com tudo)
                for(itR=R.begin(); itR!=R.end(); itR++){

                    if(*itR == pop[indN1].pop[i]){

                        R.erase(itR);
                        break;
                    }    

                }
            }
        
            for(int i=0; i<(data.N + tam); i++){
                
                for(itR=R.begin(); itR!=R.end(); itR++){
                    
                    if(*itR == pop[indN2].pop[i] && itR!=R.end()){

                        pop[indN1 + ((nPop)/2)].pop[random1] = pop[indN2].pop[i];

                        R.erase(itR);
                        random1++;
                        break;
                    
                    }

                    if(R.size()==0)
                        break; 
                }        

            }
        
            pop[indN1 + (nPop/2)].fitness();        
        }
        
        for(int i=0; i<(nPop/2); i++){
            
            if(pop[i].fitnessValue > pop[i + (nPop)/2].fitnessValue){
                
                pop[i].fitnessValue = pop[i + (nPop)/2].fitnessValue;
                pop[i].possible = pop[i + (nPop/2)].possible;
                
                for(int l=0; l<= (data.N+tam); l++){
                    pop[i].pop[l] = pop[i + (nPop)/2].pop[l];
                }        

            }

        }
};

int main(){

    z = 0; // start in ramdomico function
    
    data.LoadBarreto("../Instances/21x5.dat");
    data.ShowValues();
    Individuo * pop = new Individuo[nPop];

    int geracao = 1;

        for(int i=0; i<(data.N + tam); i++){
            pop[i].fitness();  
        }

    while(true){

        cout << "--------------------------------" << endl;
        cout << "----------" << geracao << "-----------------" << endl;
        geracao++;

        crossOver1(pop);
        pop[(r.next()%(data.N+tam))].mutation();

        for(int i=0; i<nPop; i++){
            pop[i].print();  
        }

        getchar();

    }
    
    return 0;
}
