#ifndef PUZZLE_H
#define PUZZLE_H
#include "stdlib.h"
#include "list"

using namespace std;

enum Posiciones{ARRIBAIZQUIERDA,ARRIBA,ARRIBADERECHA,DERECHA,ABAJODERECHA,ABAJO,ABAJOIZQUIERDA,IZQUIERDA,CENTRO};

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
        void next();

        virtual ~Puzzle();
    protected:
    private:
        map<int,map<int,Square*>> matriz;
        string name;
        int getMejorSolucion(list<Square *>, Square *&);
        list<Square *> getVecinos(Square *);
        Square * vacio;
        int resuelto;
};

list<Puzzle::Square*> Puzzle::getVecinos(Square * s){
    int pos = s->getPosicion();
    list<Square *> vecinos;
    switch(pos){
        case ARRIBAIZQUIERDA:
            vecinos.push_back(matriz[s->fil][s->col + 1]);
            vecinos.push_back(matriz[s->fil + 1][s->col]);
            break;
        case ARRIBA:
            vecinos.push_back(matriz[s->fil][s->col + 1]);
            vecinos.push_back(matriz[s->fil][s->col - 1]);
            vecinos.push_back(matriz[s->fil + 1][s->col]);
            break;
        case ARRIBADERECHA:
            vecinos.push_back(matriz[s->fil][s->col - 1]);
            vecinos.push_back(matriz[s->fil + 1][s->col]);
            break;
        case DERECHA:
            vecinos.push_back(matriz[s->fil][s->col - 1]);
            vecinos.push_back(matriz[s->fil + 1][s->col]);
            vecinos.push_back(matriz[s->fil - 1][s->col]);
            break;
        case ABAJODERECHA:
            vecinos.push_back(matriz[s->fil][s->col - 1]);
            vecinos.push_back(matriz[s->fil - 1][s->col]);
            break;
        case ABAJO:
            vecinos.push_back(matriz[s->fil][s->col + 1]);
            vecinos.push_back(matriz[s->fil][s->col - 1]);
            vecinos.push_back(matriz[s->fil - 1][s->col]);
            break;
        case ABAJOIZQUIERDA:
            vecinos.push_back(matriz[s->fil][s->col + 1]);
            vecinos.push_back(matriz[s->fil - 1][s->col]);
            break;
        case IZQUIERDA:
            vecinos.push_back(matriz[s->fil][s->col + 1]);
            vecinos.push_back(matriz[s->fil + 1][s->col]);
            vecinos.push_back(matriz[s->fil - 1][s->col]);
            break;
        case CENTRO:
            vecinos.push_back(matriz[s->fil][s->col + 1]);
            vecinos.push_back(matriz[s->fil][s->col - 1]);
            vecinos.push_back(matriz[s->fil + 1][s->col]);
            vecinos.push_back(matriz[s->fil - 1][s->col]);
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
        if(s->getValorReal() != s->valor and !temp) resultado = s;
    }
    if(!resultado){
        resultado = vecinos.front();
        return 1;
    }
    return 0;
}

void Puzzle::next(){
    Square * mejorS;
    int varianza = getMejorSolucion(getVecinos(vacio),mejorS);


}

int Puzzle::Square::getPosicion(){
    if(fil == 0){
        if(col == 0){
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
        if(col == 0){
            return ABAJOIZQUIERDA;
        }
        else{
            return ABAJO;
        }
    }
    else if(col == 0){
        return IZQUIERDA;
    }
    else return CENTRO;
}

Puzzle::Puzzle(int n, string name){
    resuelto = 0;
    this->name = name;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            ///FALTA PONER LA IMAGEN;
            int numero = rand() % n + 1;
            matriz[i][j]->_llenarValores(i,j,,n,name);
            if(numero == n) vacio = matriz[i][j];
            if(numero != matriz[i][j]->getValorReal()) resuelto++;
        }
    }
}

Puzzle::Puzzle(){
    name = nullptr;
}

int Puzzle::Square::getValorReal(){
    return n * (fil - 1) + col;
}

void Puzzle::Square::_llenarValores(int fil, int col , int val, int n, string img){
    this->fil = fil;
    this->col = col;
    this->n = n;
    valor = val;
    image = img
}

Puzzle::Square::Square(){
    vecinos[IZQUIERDA] = nullptr;
    vecinos[ARRIBA] = nullptr;
    vecinos[DERECHA] = nullptr;
    vecinos[ABAJO] = nullptr;
    image = nullptr;
    n = 0;
    fil = 0;
    col = 0;
    valor = -1;
}



Puzzle::Square::Square(int fil, int col, int val,int n, string img){
    vecinos[IZQUIERDA] = nullptr;
    vecinos[ARRIBA] = nullptr;
    vecinos[DERECHA] = nullptr;
    vecinos[ABAJO] = nullptr;
    this->fil = fil;
    this->col = col;
    this->n = n;
    valor = val;
    image = img;
}

#endif // PUZZLE_H
