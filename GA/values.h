#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>

using namespace std;

struct Coord{
    int x;
    int y;
};


struct Values{
    //Métodos de leitura
    Values();
    ~Values();

    void LoadBarreto(string file); //Lê valores do arquivo passado (Instâncias Barreto)
    void ShowValues(); //Imprime os valores lidos


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

    map<int, Coord> coordC; //Conjunto de coordenadas dos consumidores
    map<int, Coord> coordD; //Conjunto de coordenadas dos depósitos

};