#include <iostream>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "values.h"
#define nPop 1024
#define nRand 100000
#define nCross 256

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
    double fitnessValue; 
    bool possible;
    double carroNow; 
    int depotNow;
    double depotNowValue;
    int wayNow;
    bool depotNowOpen;
    double atual;

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

    double fitness(){              // calculate and return the fitness value of i individual
        
        fitnessValue = 0;
        carroNow = 0;
        depotNow = pop[0];
        depotNowOpen = 0;
        wayNow = pop[0];
        depotNowValue = 0;
        possible = true;

        for(int i=1; i<(data.N + tam); i++){

            if(pop[i]==-1){ // it's a dummy

                if(carroNow != 0){ // if the car is not empty

                    fitnessValue += data.FV;
                    wayNow = depotNow;
                    carroNow = 0;

                } else { // if the car is empty

                    wayNow = depotNow;
                    carroNow = 0;

                }


            } else if (pop[i] < data.No){ // it's a depot

                if(depotNowOpen==0) { //previous depot not opened

                    depotNow = pop[i]; 
                    depotNowValue = 0;
                    wayNow = pop[i];
                    carroNow = 0;
                    

                } else { //previous depot opened

                    if(carroNow != 0){

                        fitnessValue += data.FV;
                         
                    }

                    fitnessValue += data.FD[depotNow];
                    wayNow = pop[i];     
                    carroNow = 0;
                    depotNow = pop[i]; 
                    depotNowOpen = 0;
                    depotNowValue = 0;

                }


            } else { //it's a costumer

                if((depotNow + data.d[i]) <= data.CD[depotNow]){ // if depot is enough

                    if((carroNow + data.d[i]) <= data.CV){ // if the atual car is enough

                        carroNow += data.d[i];
                        depotNowValue += data.d[i];
                        fitnessValue += data.c[wayNow][pop[i]];
                        wayNow = pop[i];
                        depotNowOpen = true;

                    } else { // new car required
                        
                        carroNow = data.d[i];
                        depotNowValue += data.d[i];
                        fitnessValue += data.c[depotNow][pop[i]];
                        wayNow = pop[i];
                        depotNowOpen = true;

                    }

                } else {
                    
                    carroNow += data.d[i];
                    depotNowValue += data.d[i];
                    fitnessValue += data.c[depotNow][pop[i]];
                    fitnessValue += depotNowValue - data.CD[depotNow];
                    possible = false;
                    depotNowOpen = true;
                    
                }

                if(i == (data.N + tam)-1){
                    
                    if(depotNowOpen){

                        fitnessValue += data.FD[depotNow]; 

                    }

                    if(carroNow !=0){
                        
                        fitnessValue += data.FV;

                    }

                }

            }

        }

        return fitnessValue;

    }
    
    void mutation(int melhorAtual){

        int randomN1;
        int randomN2;

        do{
            randomN1 = (r.next() % (data.N + tam));       
            randomN2 = (r.next() % (data.N + tam));
            if(randomN1==0) randomN1++;
            if(randomN2==0) randomN2++;

        } while(randomN1==melhorAtual || randomN2==melhorAtual);

        double melhor = this->fitness();
        aux = pop[randomN1]; 
        pop[randomN1] = pop[randomN2];
        pop[randomN2] = aux; 

        if(melhor > this->fitness()){

            aux = pop[randomN1]; 
            pop[randomN1] = pop[randomN2];
            pop[randomN2] = aux; 

        }

        this->fitness();    
    }

    void print(){
        
        for(int i=0; i<(data.N + tam); i++){

            cout << pop[i] << " ";

        } 

        cout << "Fitness: " << fixed << setprecision(2) << this->fitness() << " Possivel: " << possible  << endl;

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
            
        }
        
        for(int i=0; i<(nPop/2); i++){
            
            if((pop[i].fitness() > pop[i + (nPop)/2].fitness())){

                for(int l=0; l<= (data.N+tam); l++){
                    pop[i].pop[l] = pop[i + (nPop)/2].pop[l];
                }        
                
                pop[i].fitness();

            }

        }
};

int main(){

    z = 0; // start in ramdomico function
    
    data.LoadBarreto("../Instances/21x5.dat");
    data.ShowValues();
    Individuo * geracao = new Individuo[nPop];

    int ger = 1;

    int melhor = 0;

   // getchar();
    int melhorContador=0;
    double melhorComp=0;
    double atual;

    for(int j=0; j<8000; j++){
        
        cout << "--------------------------------" << endl;
        cout << "----------" << ger << "-----------------" << endl;
        ger++;

        crossOver1(geracao);
        
        for(int i=0; i<35; i++)
            geracao[r.next() % nPop].mutation(melhor);
 
        melhor = 0;
        for(int i=0; i<nPop; i++){

            if(geracao[i].fitness() < geracao[melhor].fitness() && geracao[i].possible == 1)
                melhor = i;

            geracao[i].print();  

        }
        
        atual = geracao[melhor].fitness();

        cout << "--------------------------------" << endl;
        cout << "Melhor Resultado---" << melhor << ": ----" << fixed << setprecision(2) << atual << endl;
/*
        if(melhorComp == atual){
            melhorContador++;
            if(melhorContador>=(nPop/2) || melhorContador>=100)
                break;
        } else {

            melhorComp = atual;
            melhorContador = 0;

        } 

*/
    }
    
    return 0;
}
