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

double fitness(Individuo &ind, Values &data){

	ind.fitnessValue = 0;
	ind.possible = true;
    double carroNow = 0;
    int depotNow = ind.pop[0];
    bool depotNowOpen = 0;
    int wayNow = ind.pop[0];
    double depotNowValue = 0;
        
	//cout << "Entrou no fitness com:" << endl;
	//cout << "Ind.tam: " << ind.tam << " fitness value = " << ind.fitnessValue << endl;

        for(int i=1; i<ind.tam; i++){

            if(ind.pop[i]==-1){ // it's a dummy

                if(carroNow != 0){ // if the car is not empty

                    ind.fitnessValue += data.FV;
                    wayNow = depotNow;
                    carroNow = 0;

                } else { // if the car is empty

                    wayNow = depotNow;
                    carroNow = 0;

                }


            } else if (ind.pop[i] < data.No){ // it's a depot

                if(depotNowOpen==0) { //previous depot not opened

                    depotNow = ind.pop[i]; 
                    depotNowValue = 0;
                    wayNow = ind.pop[i];
                    carroNow = 0;
                    

                } else { //previous depot opened

                    if(carroNow != 0){

                        ind.fitnessValue += data.FV;
                         
                    }
		            
                    //cout << "Entra AQUI" << endl;
                    ind.fitnessValue += data.FD[depotNow];
                    wayNow = ind.pop[i];     
                    carroNow = 0;
                    depotNow = ind.pop[i]; 
                    depotNowOpen = 0;
                    depotNowValue = 0;

                }


            } else { //it's a costumer

                if((depotNow + data.d[ind.pop[i]]) <= data.CD[depotNow]){ // if depot is enough

                    if((carroNow + data.d[ind.pop[i]]) <= data.CV){ // if the atual car is enough

                        carroNow += data.d[ind.pop[i]];
                        depotNowValue += data.d[ind.pop[i]];
                        ind.fitnessValue += data.c[wayNow][ind.pop[i]];
                        wayNow = ind.pop[i];
                        depotNowOpen = true;

                    } else { // new car required
                        
                        carroNow = data.d[ind.pop[i]];
                        depotNowValue += data.d[ind.pop[i]];
                        ind.fitnessValue += data.c[depotNow][ind.pop[i]];
                        wayNow = ind.pop[i];
                        depotNowOpen = true;

                    }

                } else {
                    
                    carroNow += data.d[ind.pop[i]];
                    depotNowValue += data.d[ind.pop[i]];
                    ind.fitnessValue += data.c[depotNow][ind.pop[i]];
                    ind.fitnessValue += depotNowValue - data.CD[depotNow];
                    ind.possible = false;
                    depotNowOpen = true;
                    
                }

                if(i == ind.tam-1){
                    
                    if(depotNowOpen){
			
		            //	cout << "Entra AQUI" << endl;
                        ind.fitnessValue += data.FD[depotNow]; 

                    }

                    if(carroNow !=0){
                        
                        ind.fitnessValue += data.FV;

                    }

                }

            }

	}

	//cout << "Fitness value: " << ind.fitnessValue << endl;
}

void crossOver1(Individuo * pop, Values &data, randomico &r){

        int indN1, indN2, random1, random2;
        int tamAux;
        vector<int> aux;
        vector<int> RDepot;         
        vector<int> R;
        vector<int>::iterator itR;

        for(int j=0; j<nCross; j++){

            indN1 = (r.next() % (nPop/2));       
            indN2 = (r.next() % (nPop/2));
            random1 = (r.next() % (pop[0].tam));

            if(random1 == 0) 
                random1++;
                
            aux.clear();
            RDepot.clear();
            R.clear();
            
            // mesclar pop[indN1] com pop[indN2] a partir do nodo random1

            for(int i=0; i<data.N; i++){
                
                R.push_back(i);
                
            }

            int soma=0; 

            for(int i=data.No; i<data.N; i++){
                
                soma += data.d[i];

            }

            tamAux = soma / data.CV;

            for(int i=0; i<tamAux; i++){

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

        
            for(int i=0; i<pop[0].tam; i++){
                
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
            
        }
        
        for(int i=0; i<(nPop/2); i++){
            
            if((pop[i].fitnessValue > pop[i + (nPop)/2].fitnessValue)){

                fitness(pop[i], data);
                fitness(pop[i + (nPop)/2], data);

                for(int l=0; l<= pop[0].tam; l++){
                    pop[i].pop[l] = pop[i + (nPop)/2].pop[l];
                }        

                pop[i].fitnessValue = pop[i + (nPop)/2].fitnessValue;
                pop[i].possible = pop[i + (nPop)/2].possible;

            }

        }
};



int main(){

	Values data;
	randomico r;
	data.LoadBarreto("../Instances/21x5.dat");
    	data.ShowValues();

	//int vet[] = {0,1,12,10,7,8,-1,14,13,11,9,6,5,-1,15,2,3,-1,17,-1,20,18,16,19,-1,21,24,22,-1,23,25,4};
	//Individuo ind(vet, 32);
	//ind.print();
	//fitness(ind, data);

    Individuo pop[nPop];
    for(int i=0; i<nPop; i++)
        pop[i].preenche(data, r);

    for(int i=0; i<nPop; i++){
        fitness(pop[i], data);
        pop[i].print();
    }

    for(int i=0; i<400; i++)
        crossOver1(pop, data, r);

    for(int i=0; i<nPop; i++){
        fitness(pop[i], data);
        pop[i].print();
    }	
    
	return 0; 
} 
