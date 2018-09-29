#include "Values.h"

Values2::Values2(){}

Values2::~Values2(){}

void Values2::LoadBarreto(string file){
    ifstream data(file.c_str());
    
    if(!data.is_open()){
        cerr << "ERROR: Nao foi possivel abrir o arquivo" << endl;
        throw(-1);
    }

    //Read the number of costumers and available depots
    string aux;
    getline(data, aux); Nc = stoi(aux);
    getline(data, aux); No = stoi(aux);
    N = Nc+No;

    int i, j;
    //Create arrays
    CD = new int [No];
    FD = new int [No]; 
    d = new int [Nc];
    //Create matrix
    c = new float* [N];
    for(i=0; i<N; i++)
        c[i] = new float [N];

    Coord2 auxDist[this->N];  //Temporário, retirar para eficiencia!!!!!!!!
    Coord2 auxCoord2;
    //Read the coord2Coord2inates for the depots (x and y)
    getline(data, aux);
    for(i=0; i<No; i++){
        getline(data, aux, ' '); auxCoord2.x = stoi(aux);
        getline(data, aux); auxCoord2.y = stoi(aux);
        coord2D.insert(make_pair(i, auxCoord2));
        auxDist[i] = auxCoord2;
    }

    //Read the coord2Coord2inates for the customers
    getline(data, aux);
    for(i=0; i<Nc; i++){
        getline(data, aux, ' '); auxCoord2.x = stoi(aux);
        getline(data, aux); auxCoord2.y = stoi(aux);
        coord2C.insert(make_pair(i, auxCoord2));
        auxDist[i+No] = auxCoord2;
    }

    //Calculate the matrix of distances
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            c[i][j] = sqrt(pow((auxDist[i].x-auxDist[j].x), 2) + pow(auxDist[i].y-auxDist[j].y, 2));
        }
    }

    //Read the vehicle capacity
    getline(data, aux);
    getline(data, aux);
    this->CV = stoi(aux);

    //Read the vehicle capacities
    getline(data, aux);
    for(i=0; i<No; i++){
        getline(data, aux); this->CD[i] = stoi(aux);
    }

    //Read the customers demands
    getline(data, aux);
    for(i=0; i<Nc; i++){
        getline(data, aux); this->d[i] = stoi(aux);
    }

    //Read the opening costs for the depots
    getline(data, aux);
    for(i=0; i<No; i++){
        getline(data, aux); this->FD[i] = stoi(aux);
    }

    //Read opening cost of a route
    getline(data, aux);
    getline(data, aux); this->FV = stoi(aux);
}

void Values2::ShowValues2(){
    int i, j;
    cout << "Nc: " << Nc << " " << "No: " << No << " N: " << N << endl;
    cout << "Coord2enadas dos depósitos" << endl;
    map<int, Coord2>::iterator it;
    for(it=coord2D.begin(); it!=coord2D.end(); it++){
        cout << it->second.x << " " << it->second.y << endl;
    }
    cout << "Coord2enadas dos consumidores" << endl;
    for(it=coord2C.begin(); it!=coord2C.end(); it++){
        cout << it->second.x << " " << it->second.y << endl;
    }
    cout << "Capacidade do veículo" << endl;
    cout << this->CV << endl;
    cout << "Capacidades dos depósitos" <<endl;
    for(i=0; i<No; i++){
        cout << this->CD[i] << endl;
    }
    cout << "Demanda dos consumidores" <<endl;
    for(i=0; i<Nc; i++){
        cout << this->d[i] << endl;
    }
    cout << "Custo de abertura dos depositos" <<endl;
    for(i=0; i<No; i++){
        cout << this->FD[i] << endl;
    }
    cout << "Custo da rota" << endl;
    cout << this->FV << endl;

    cout << "Matriz de distâncias" << endl;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            cout << setprecision(3) << setw(4) << c[i][j] << " ";
        }
        cout << endl;
    }
}