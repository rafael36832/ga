#include <iostream>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "values.h"
#define nPop 1024
#define nRand 100000

    
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
        for(int i=1; i<nPop; i++){

            if(geracao[i].fitness() < geracao[melhor].fitness() && geracao[i].possible == 1)
                melhor = i;

            geracao[i].print();  

        }
        
        atual = geracao[melhor].fitness();

        cout << "--------------------------------" << endl;
        cout << "Melhor Resultado---" << melhor << ": ----" << fixed << setprecision(2) << atual << endl;
    
        if(melhorComp == atual){
            melhorContador++;
            if(melhorContador>=(nPop/2) || melhorContador>=100)
                break;
        } else {

            melhorComp = atual;
            melhorContador = 0;

        } 


    }
    
    return 0;
}
