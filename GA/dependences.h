#include <iostream>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <cstring>

class randomico{
public:

    int * aleatorio;
    int z;
	int nRand;

    randomico(int nRand){	

		this->nRand = nRand;
		aleatorio = new int[nRand];
	    z=0;

		srand(time(NULL));

        for(int i=0; i<nRand; i++){

            aleatorio[i] = rand();

        } 

    }

    int next(){

		z++;          
        if(z >= this->nRand-1)
            z = 0;
			
		return aleatorio[z];    

    }
};

class Individuo {

public:
	
    int * pop;         // pindividual vector
    double fitnessValue; 
   	bool possible;   
	int tam;   

	Individuo(){

		possible = false;

	}

	Individuo(int * vet, int vectorSize){
		
		tam = vectorSize;
		pop = new int[tam];	

		for(int i=0; i<tam; i++){		
			pop[i] = vet[i];			

		}

	}

	void preenche (Values &data, randomico &r){
		
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

    void print(){
        
        for(int i=0; i<tam; i++){

            cout << pop[i] << " ";

        } 

        cout << "Fitness: " << fixed << setprecision(2) << fitnessValue << " Possivel: " << possible  << endl;

    }

};
