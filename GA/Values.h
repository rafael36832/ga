#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>

using namespace std;

struct Coord2{
    int x;
    int y;
};


struct Values2{
    //Métodos de leitura
    Values2();
    ~Values2();

    void LoadBarreto(string file); //Lê valores do arquivo passado (Instâncias Barreto)
    void ShowValues2(); //Imprime os valores lidos


    int No; //Number of depots
    int Nc; //Number of costumers
    int N; //Total of depots and constumers
    int CV; //vehicle capacity
    int FV; //vehicle fixed cost(route)
    int* CD; //depots capacity
    int* FD; //depots fixed cost
    int* d; //costumers demand

    float** c; //matrix distance(real) (i,j pertence a N)
               //distância entre o nodo i e o nodo j

    map<int, Coord2> coord2C; //Conjunto de coord2enadas dos consumidores
    map<int, Coord2> coord2D; //Conjunto de coord2enadas dos depósitos

};