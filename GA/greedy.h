#pragma once

#include <vector>
#include <map>
#include <limits>
#include <random>
#include <cmath>
#include <iterator>
#include <unistd.h>
#include "Values.h"

using namespace std;

bool Pertence(int a, int n){ 
    for(int i=1; i<=n; i++){
        if(a == i)
            return true;
    }
    return false;
}

void LKopt(vector<int> &r, int x, int y){
    int pos1 = x;
    int pos2 = y;
    int aux;

    if(pos2 > pos1){
        aux = pos1;
        pos1 = pos2;
        pos2 = aux;
    }

    for(int i=pos2, k=pos1; i<k; i++, k--){
        aux = r[i];
        r[i] = r[k];
        r[k] = aux;
    }
}

vector<int> LKalg(Values2 &data, map<int, Coord2> &assigned, vector<int> &route ){
    int i, j;
    for(i=0; i<route.size()-1; i++){
        for(j=i+1; j<route.size(); j++){
            if(data.c[route[i]][route[i+1]] - data.c[route[i]][route[j]] > 0){
                LKopt(route, i+1, j);
            }
        }
    }

    return route;
}

//Retorna qual depósito tem mais consumidores próximos
int MoreCCDepot(Values2 &data){
    double aux, dist;
    int pos;
    map<int, Coord2>::iterator itC, itD;
    vector< map<int, Coord2> > Ul(data.No); //'Costumers' mais próximos do depósito
    for(itC = data.coord2C.begin(); itC != data.coord2C.end(); itC++){
        aux = 99999;
        //Verifica qual depósito é o mais próximo do cliente
        for(itD = data.coord2D.begin(); itD != data.coord2D.end(); itD++){
            //dist = sqrt(pow((itC->second.x-itD->second.x), 2) + pow((itC->second.y-itD->second.y), 2));
            dist = data.c[itC->first+data.No][itD->first];
            if(dist < aux){
                pos = itD->first;
                aux = dist;
            }
        }
        Ul[pos].insert(make_pair(itC->first, itC->second));
    }
    //Checa qual cc é maior
    int k=0;
    for(int i=0; i<data.No; i++){
        if(Ul[i].size() > Ul[k].size()){
            k=i;
        }
    }
    return k;
}

//Preenche o vetor passado como referência com os consumidores mais próximos do depósito
void NearCostumers(Values2 &data, map<int, Coord2> &assigned, int k){
    double dist;
    int pos;
    int used_cap = 0;
    map<int, Coord2>::iterator itC, it_temp;    
    while(used_cap < data.CD[k]){
        double aux = numeric_limits<double>::max();
        for(itC = data.coord2C.begin(); itC != data.coord2C.end(); itC++){
            dist = data.c[k][data.No+itC->first];
            if(dist<aux){
                aux = dist;
                it_temp = itC;
            }
        }
        if(used_cap+data.d[it_temp->first] < data.CD[k]){
            used_cap += data.d[it_temp->first];
            data.coord2C.erase(it_temp->first);
            assigned.insert(make_pair(it_temp->first, it_temp->second));
        } else break;
    }
}

vector<int> GreedyAlg(Values2 &data){

    map<int, Coord2> assigned;
    vector< int > result;

    //"Variáveis de decisão"
    bool y[data.No]; //Se o depósito é aberto
    for(int i=0; i<data.No; i++)
        y[i] = 0;

    int i, j, k;
    while(data.coord2C.size() > 0){
        k = MoreCCDepot(data); //Depósito com mais consumidores próximos

        y[k] = 1;

        NearCostumers(data, assigned, k); //Atribui ao depósito os consumidores

        map<int, Coord2>::iterator it;

        //MakeRoute(data, assigned, result, k); //Gera as rotas dos veículos
        vector< int > route;

        cout << "Assigned LK" << k << ": ";
        for(it = assigned.begin(); it!=assigned.end(); it++){
            cout << it->first + 1 << " ";
            route.push_back(it->first+data.No);
        }
        cout << endl;

        cout << "route1 LK" << k << ": ";
        for(int i = 0; i<route.size(); i++){
            cout << route[i] + 1 << " ";
        }
        cout << endl;

        route = LKalg(data, assigned, route); //Algoritmo TSP com os consumidores mais próximos

        result.push_back(k+1);
        cout << "route2 LK" << k << ": ";
        for(int i = 0; i<route.size(); i++){
            cout << route[i] + 1 << " ";
            result.push_back(route[i]+1);
        }
        cout << endl;        

        assigned.clear();
    }

    //Insere depósitos que não foram abertos
    for(i=0; i<data.No; i++){
        if(y[i] == 0){ //Se o depósito está fechado
            for(j=0; j<result.size(); j++)
                if(result[j] == i+2 && Pertence(i+2, data.No))
                    break;
            result.insert(result.begin()+j, i+1);
        }
    }

    for(int i=0; i<result.size(); i++){
        cout << result[i] << " ";
    }
    cout << endl;

    return result;
}