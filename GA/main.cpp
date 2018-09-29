#include <iostream>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "values.h"
#include "Values.h" 
#include "dependences.h" 
#include "greedy.h"
#define nPop 128
#define nRand 1000000
#define nCross 100000000
#define MAXREP 100000
#define NMUTATION 32

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

        for(int i=0; i<=ind.tam; i++){

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

                if((depotNowValue + data.d[ind.pop[i]]) <= data.CD[depotNow]){ // if depot is enough

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
                    ind.fitnessValue += (depotNowValue - data.CD[depotNow]);
                    ind.possible = false;
                    depotNowOpen = true;
                    
                }

                if(i == ind.tam ){
                    
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

void crossOver1(Individuo * pop, Values &data, randomico &r, double &melhor, int &indMelhor){

    int indN1, indN2, random1, random2;
    int tamAux;
    vector<int> aux;
    vector<int> RDepot;         
    vector<int> R;
    vector<int>::iterator itR;

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

    fitness(pop[indN1 + (nPop)/2], data);
    fitness(pop[indN1], data);

    if((pop[indN1].fitnessValue > pop[indN1 + (nPop)/2].fitnessValue) && pop[indN1 + (nPop)/2].possible){

        for(int l=0; l<= pop[0].tam; l++){
            pop[indN1].pop[l] = pop[indN1 + (nPop)/2].pop[l];
        }        

        fitness(pop[indN1], data);
    }   

    if((pop[indN1].fitnessValue < pop[indMelhor].fitnessValue) && pop[indN1].possible){
        indMelhor = indN1; 
        melhor = pop[indN1].fitnessValue;
    }
};

void mutation(Individuo &ind, Values &data, randomico &r){ /// beeeem arcaica ainda

    int randomN1;
    int randomN2;
    
    randomN1 = (r.next() % (ind.tam));       
    randomN2 = (r.next() % (ind.tam));
    if(randomN1==0) randomN1++;
    if(randomN2==0) randomN2++;
    if(randomN1==(ind.tam)) randomN1--;
    if(randomN2==(ind.tam)) randomN2--;

    int aux;
    aux = ind.pop[randomN1];
    ind.pop[randomN1] = ind.pop[randomN2];
    ind.pop[randomN2] = aux;

}

int main(){

    // inicialização e leitura dos dados
    int NRand = nRand;
	Values data;
	randomico r(NRand);

	data.LoadBarreto("../Instances/21x5.dat");
    data.ShowValues();

    double melhor=9999999999;
    int indMelhor=0;

    Individuo pop[nPop];
  
    for(int i=0; i<nPop; i++){

        pop[i].preenche(data, r);
        fitness(pop[i], data);

        if((pop[i].fitnessValue < melhor) && pop[i].possible){
            melhor = pop[i].fitnessValue;
            indMelhor = i;
        }

    }
    // crossOver e taxa de mutação
    int aux;
    double anterior = melhor; 
    int contConvergencia=0;

    for(int i=0; i<nCross; i++){

        crossOver1(pop, data, r, melhor, indMelhor); // Chama o crossOver aleatório	

        if (i%NMUTATION==0){ // Faz mutação

            do{
                aux = r.next()%(pop[1].tam);
            
            } while(aux==indMelhor);
            
            mutation(pop[aux], data, r);
            fitness(pop[aux], data);

            if((pop[aux].fitnessValue < pop[indMelhor].fitnessValue) && pop[aux].possible){

                indMelhor = aux;
                melhor = pop[aux].fitnessValue;
            }
            
        }

        // Verifica se tá com o mesmo resultado depois de muito tempo
        if(anterior == melhor){
            contConvergencia++;
        } else {
            contConvergencia =0;
            anterior = melhor;
        }
        if(contConvergencia >= MAXREP){
            cout << "Saiu depois de " << contConvergencia << " operações com o mesmo resultado" << endl;
            break;
        }
    }
/*
    for(int i=0; i<nPop; i++){
        fitness(pop[i], data);
        pop[i].print();
    }	
*/    
    cout << endl;
    cout << "Melhor : POP[" << indMelhor << "] = " << melhor << endl;
    pop[indMelhor].print();

    Values2 data2;
	data2.LoadBarreto("../Instances/21x5.dat");
    vector<int> teste2;
    teste2 = GreedyAlg(data2); 

    int vet[teste2.size()];

    cout << "----------------" << endl;
    for (int i=0; i<teste2.size(); i++){
        cout << teste2[i] << " ";
        vet[i] = teste2[i] -1; 
    }

    cout << endl;

    Individuo individual(vet,teste2.size());
    fitness(individual, data);
    individual.print();

    return 0; 
} 
