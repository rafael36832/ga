#include "values.h"

Values::Values(){}

Values::~Values(){}

void Values::LoadBarreto(string file){
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

    Coord auxDist[this->N];  //Temporário, retirar para eficiencia!!!!!!!!
    Coord auxCoord;
    //Read the coordinates for the depots (x and y)
    getline(data, aux);
    for(i=0; i<No; i++){
        getline(data, aux, ' '); auxCoord.x = stoi(aux);
        getline(data, aux); auxCoord.y = stoi(aux);
        coordD.insert(make_pair(i, auxCoord));
        auxDist[i] = auxCoord;
    }

    //Read the coordinates for the customers
    getline(data, aux);
    for(i=0; i<Nc; i++){
        getline(data, aux, ' '); auxCoord.x = stoi(aux);
        getline(data, aux); auxCoord.y = stoi(aux);
        coordC.insert(make_pair(i, auxCoord));
        auxDist[i+No] = auxCoord;
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

void Values::ShowValues(){
    int i, j;
    cout << "Nc: " << Nc << " " << "No: " << No << " N: " << N << endl;
    cout << "Coordenadas dos depósitos" << endl;
    map<int, Coord>::iterator it;
    for(it=coordD.begin(); it!=coordD.end(); it++){
        cout << it->second.x << " " << it->second.y << endl;
    }
    cout << "Coordenadas dos consumidores" << endl;
    for(it=coordC.begin(); it!=coordC.end(); it++){
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