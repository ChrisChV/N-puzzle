#ifndef PUZZLE_H
#define PUZZLE_H
#include "stdlib.h"
#include "list"
#include "algorithm"
#include "vector"
#include "map"
#include "ArbolDeJuego.h"

using namespace std;

enum Posiciones{ARRIBAIZQUIERDA,ARRIBA,ARRIBADERECHA,DERECHA,ABAJODERECHA,ABAJO,ABAJOIZQUIERDA,IZQUIERDA,CENTRO};

class Puzzle;

void desple(Puzzle actual, list<tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto);

class Puzzle
{
    public:
        class Square{
            public:
                Square();
                Square(int,int,int,int,string);
                void _llenarValores(int,int,int,int,string);
                int getValorReal();
                int getPosicion();
                int fil;
                int col;
                int valor;
                int n;
                string image;
        };
        Puzzle();
        Puzzle(int,string);
        Puzzle(map<int,map<int,Square*>>,string,Square*,int);
        void next();
        map<int,map<int,Square*>> getMatriz(){return matriz;};
        void print();
        int estaResuelto();
        void Resolver();
        Puzzle copiarPuzzle();
        Square * getVacio();
        int getValor(Square *);
        void swapValores(Square *);
        list<Square *> getVecinos(Square *,Square *);
        Square * vacio;
        virtual ~Puzzle();
    protected:
    private:
        map<int,map<int,Square*>> matriz;
        string name;
        int getMejorSolucion(list<Square *>, Square *&);

        int resuelto;
        void nextPorPaso(list<Puzzle>&);
        ArbolDeJuego<Puzzle> juego;
};



Puzzle::Puzzle(map<int,map<int,Square*>> matriz,string name, Square * vacio, int resuelto){
    this->matriz = matriz;
    this->name = name;
    this->vacio = vacio;
    this->resuelto = resuelto;
}

void Puzzle::swapValores(Square * vecino){
    swap(vacio->valor,vecino->valor);
    swap(vacio->image,vecino->image);
    vacio = vecino;
}

int Puzzle::getValor(Square * vecino){
    if(vecino->getValorReal() == vecino->valor)return 1;
    if(vacio->getValorReal() == vecino->valor)return -1;
    return 0;
}

Puzzle::Square * Puzzle::getVacio(){
    return vacio;
}

int Puzzle::estaResuelto(){
    return resuelto;
}

void Puzzle::print(){
    for(int i = 1; i <= matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            cout<<matriz[i][j]->valor<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

list<Puzzle::Square*> Puzzle::getVecinos(Square * s, Square * anterior){
    int pos = s->getPosicion();
    list<Square *> vecinos;
    switch(pos){
        case ARRIBAIZQUIERDA:
            if(matriz[s->fil][s->col + 1] != anterior) vecinos.push_back(matriz[s->fil][s->col + 1]);
            if(matriz[s->fil + 1][s->col] != anterior) vecinos.push_back(matriz[s->fil + 1][s->col]);
            break;
        case ARRIBA:
            if(matriz[s->fil][s->col - 1] != anterior) vecinos.push_back(matriz[s->fil][s->col - 1]);
            if(matriz[s->fil][s->col + 1] != anterior) vecinos.push_back(matriz[s->fil][s->col + 1]);
            if(matriz[s->fil + 1][s->col] != anterior) vecinos.push_back(matriz[s->fil + 1][s->col]);
            break;
        case ARRIBADERECHA:
            if(matriz[s->fil][s->col - 1] != anterior) vecinos.push_back(matriz[s->fil][s->col - 1]);
            if(matriz[s->fil + 1][s->col] != anterior) vecinos.push_back(matriz[s->fil + 1][s->col]);
            break;
        case DERECHA:
            if(matriz[s->fil][s->col - 1] != anterior) vecinos.push_back(matriz[s->fil][s->col - 1]);
            if(matriz[s->fil - 1][s->col] != anterior) vecinos.push_back(matriz[s->fil - 1][s->col]);
            if(matriz[s->fil + 1][s->col] != anterior) vecinos.push_back(matriz[s->fil + 1][s->col]);
            break;
        case ABAJODERECHA:
            if(matriz[s->fil][s->col - 1] != anterior) vecinos.push_back(matriz[s->fil][s->col - 1]);
            if(matriz[s->fil - 1][s->col] != anterior) vecinos.push_back(matriz[s->fil - 1][s->col]);
            break;
        case ABAJO:
            if(matriz[s->fil][s->col - 1] != anterior) vecinos.push_back(matriz[s->fil][s->col - 1]);
            if(matriz[s->fil - 1][s->col] != anterior) vecinos.push_back(matriz[s->fil - 1][s->col]);
            if(matriz[s->fil][s->col + 1] != anterior) vecinos.push_back(matriz[s->fil][s->col + 1]);
            break;
        case ABAJOIZQUIERDA:
            if(matriz[s->fil - 1][s->col] != anterior) vecinos.push_back(matriz[s->fil - 1][s->col]);
            if(matriz[s->fil][s->col + 1] != anterior) vecinos.push_back(matriz[s->fil][s->col + 1]);
            break;
        case IZQUIERDA:
            if(matriz[s->fil - 1][s->col] != anterior) vecinos.push_back(matriz[s->fil - 1][s->col]);
            if(matriz[s->fil][s->col + 1] != anterior) vecinos.push_back(matriz[s->fil][s->col + 1]);
            if(matriz[s->fil + 1][s->col] != anterior) vecinos.push_back(matriz[s->fil + 1][s->col]);
            break;
        case CENTRO:
            if(matriz[s->fil][s->col - 1] != anterior) vecinos.push_back(matriz[s->fil][s->col - 1]);
            if(matriz[s->fil - 1][s->col] != anterior) vecinos.push_back(matriz[s->fil - 1][s->col]);
            if(matriz[s->fil][s->col + 1] != anterior) vecinos.push_back(matriz[s->fil][s->col + 1]);
            if(matriz[s->fil + 1][s->col] != anterior) vecinos.push_back(matriz[s->fil + 1][s->col]);
            break;
    }
    return vecinos;
}

int Puzzle::getMejorSolucion(list<Square *> vecinos, Square *& resultado){
    resultado = nullptr;
    for(Square * s : vecinos){
        if(vacio->getValorReal() == s->valor){
            resultado = s;
            return -1;
        }
        if(s->getValorReal() != s->valor and !resultado){
            resultado = s;
        }
    }
    if(!resultado){
        resultado = vecinos.front();
        return 1;
    }
    return 0;
}

void Puzzle::Resolver(){
    print();
    char t;
    cin>>t;
    while(resuelto){
        next();
    }
}

void Puzzle::nextPorPaso(list<Puzzle>& camino){
    for(Puzzle p : camino){
        matriz = p.getMatriz();
        ///Lentearlo;
        print();
        char t;
        cin>>t;
    }
}

void Puzzle::next(){
    list<Puzzle> camino;
    while(!juego.desplegar(camino)){
        camino.clear();
    }
    nextPorPaso(camino);
    resuelto--;
}

int Puzzle::Square::getPosicion(){
    if(fil == 1){
        if(col == 1){
            return ARRIBAIZQUIERDA;
        }
        else if(col == n){
            return ARRIBADERECHA;
        }
        else{
            return ARRIBA;
        }
    }
    else if(col == n){
        if(fil == n){
            return ABAJODERECHA;
        }
        else{
            return DERECHA;
        }
    }
    else if(fil == n){
        if(col == 1){
            return ABAJOIZQUIERDA;
        }
        else{
            return ABAJO;
        }
    }
    else if(col == 1){
        return IZQUIERDA;
    }
    else return CENTRO;
}

Puzzle::Puzzle(int n, string name){
    void (*des)(Puzzle, list<tuple<int,Puzzle>>&, Puzzle, int);
    des = desple;
    juego = ArbolDeJuego<Puzzle>(-1,1,des);
    resuelto = 0;
    this->name = name;
    vector<int> valores;
    for(int i = 1; i <= n * n; i++){
        valores.push_back(i);
    }
    for(int i = 1; i <= n; i++){
        if(valores.empty())break;
        for(int j = 1; j <= n; j++){
            ///FALTA PONER LA IMAGEN;
            int h = rand() % valores.size();
            int numero = valores[h];
            matriz[i][j] = new Square(i,j,numero,n,name);
            if(numero == n * n) vacio = matriz[i][j];
            if(numero != matriz[i][j]->getValorReal()) resuelto++;
            valores.erase(valores.begin() + h);
        }
    }
    juego.insert(Puzzle(matriz,name,vacio,resuelto));
}

Puzzle::Puzzle(){
    name = "default";
}

int Puzzle::Square::getValorReal(){
    return n * (fil - 1) + col;
}

void Puzzle::Square::_llenarValores(int fil, int col , int val, int n, string img){
    this->fil = fil;
    this->col = col;
    this->n = n;
    valor = val;
    image = img;
}

Puzzle::Square::Square(){
    image = nullptr;
    n = 0;
    fil = 0;
    col = 0;
    valor = -1;
}



Puzzle::Square::Square(int fil, int col, int val,int n, string img){
    this->fil = fil;
    this->col = col;
    this->n = n;
    valor = val;
    image = img;
}

Puzzle::~Puzzle(){
    for(int i = 1; i <= matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            delete matriz[i][j];
        }
    }
}

void desple(Puzzle actual, list<tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto){
    list<Puzzle::Square *> vecinos = actual.getVecinos(actual.getVacio(),anterior.getVacio());
    Puzzle temp = actual;
    for(Puzzle::Square * s : vecinos){
        actual = temp;
        int valor = actual.getValor(s);
        if(valor != valorIncorrecto){
            actual.swapValores(s);
            resultado.push_back(make_tuple(valor,actual));
        }
    }
}


#endif // PUZZLE_H
