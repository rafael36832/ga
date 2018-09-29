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

    randomico(int nRand);
    int next();

};

class Individuo {

public:
	
    int * pop;         // pindividual vector
    double fitnessValue; 
   	bool possible;   
	int tam;   

	Individuo();
	Individuo(int * vet, int vectorSize);
	void preenche (Values &data, randomico &r);
    void print();
};
