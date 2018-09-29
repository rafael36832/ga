#include <iostream>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "values.h"
#include "dependences.h"
#define nRand 1000000

randomico::randomico(int jrand){      

        aleatorio = new int[jrand];

        srand(time(0));
            
        for(int i=0; i<jrand; i++){

            aleatorio[i] = rand();

        } 

}

int randomico::next(){
        
        if(z >= nRand-1)
            z = 0;

        z++;    

        return aleatorio[z];    


}

Individuo::Individuo(){

    possible = false;

}

Individuo::Individuo(int * vet, int vectorSize){
		
	tam = vectorSize;
	pop = new int[tam];	

	for(int i=0; i<tam; i++){		
		pop[i] = vet[i];			

	}

}

////////////////////////***************************////////////////////////////////
/////////////////////////   Criar um preenche dois  ///////////////////////////////
//////////////////////                              ///////////////////////////////

 void Individuo::preenche (Values &data, randomico &r){
		
		int aux;        
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

		tam = (soma / data.CV);

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

		tam = tam + data.N;

}

void Individuo::print(){
        
        for(int i=0; i<tam; i++){

            cout << pop[i] << " ";

        } 

        cout << "Fitness: " << fixed << setprecision(2) << fitnessValue << " Possivel: " << possible  << endl;

}
