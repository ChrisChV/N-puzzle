#ifndef ARBOLDEJUEGO_H
#define ARBOLDEJUEGO_H
#include "list"
#include "tuple"

#define NOHAYINCORRECTO 1000;

using namespace std;

template<typename T>
class ArbolDeJuego
{
    public:
        class Nodo{
            public:
                Nodo();
                Nodo(T, int,int);
                T puz;
                list<Nodo *> hijos;
                Nodo * padre;
                int valor;
                int nivel;
                void destruirme();
        };
        ArbolDeJuego();
        ArbolDeJuego(int valorC,int, void (*despleG)(T,list<tuple<int,T>>&,T,int));
        bool desplegar(list<T>&);
        void insert(T puz);
        void clear();
        virtual ~ArbolDeJuego();
    protected:
    private:
        Nodo * root;
        Nodo * actual;
        int _siz;
        int _nivelActual;
        int valorCorrecto;
        int valorIncorrecto;
        void _insert(T,T);
        void (*despleG)(T,list<tuple<int,T>>&,T,int);
        bool _desplegar(Nodo *& elegido, Nodo * actual);

};

template<typename T>
void ArbolDeJuego<T>::_insert(T anterior,T elegido){
    root = new Nodo(anterior,-1000,0);
    actual = new Nodo(anterior,-1000,1);
    root->hijos.push_back(actual);
    _siz = 2;
    _nivelActual = 1;
}

template<typename T>
bool ArbolDeJuego<T>::desplegar(list<T>& camino){
    Nodo * elegido;
    if(_desplegar(elegido,root)){
        while(elegido != actual){
            camino.push_back(elegido->puz);
            elegido = elegido->padre;
        }
        clear();
        auto iter = camino.begin();
        iter++;
        _insert(*iter,camino.front());
        camino.reverse();
        return true;
    }
    return false;
}

template<typename T>
bool ArbolDeJuego<T>::_desplegar(Nodo *& elegido, Nodo * actual){
    if(!actual)return false;
    if(actual->nivel == _nivelActual){
        list<tuple<int,T>> hijos;
        T ele;
        despleG(actual->puz,hijos,actual->padre->puz,valorIncorrecto);
        for(auto t : hijos){
            Nodo * nuevo = new Nodo(get<1>(t),get<0>(t),_nivelActual + 1);
            nuevo->padre = actual;
            actual->hijos.push_back(nuevo);
            if(nuevo->valor == valorCorrecto){
                elegido = nuevo;
                return true;
            }
        }
        _siz += actual->hijos.size();
    }
    for(Nodo * h : actual->hijos){
        if(_desplegar(elegido,h))return true;
    }
    if(actual == root) _nivelActual++;
    return false;
}

template<typename T>
void ArbolDeJuego<T>::clear(){
    if(root) root->destruirme();
    root = nullptr;
    _siz = 0;
    _nivelActual = -1;
}

template<typename T>
void ArbolDeJuego<T>::insert(T puz){
    if(!root){
        Nodo * nuevo = new Nodo(puz,-1000,0);
        root = nuevo;
        actual = nuevo;
        _nivelActual = 0;
        _siz++;
    }
}

template<typename T>
void ArbolDeJuego<T>::Nodo::destruirme(){
    for(Nodo * hijo : hijos){
        hijo->destruirme();
    }
    delete this;
}

template<typename T>
ArbolDeJuego<T>::ArbolDeJuego(int valorC,int valorI, void (*despleG)(T,list<tuple<int,T>>&,T,int)){
    root = nullptr;
    this->despleG = despleG;
    valorCorrecto = valorC;
    valorIncorrecto = valorI;
    _siz = 0;
    _nivelActual = -1;
}

template<typename T>
ArbolDeJuego<T>::ArbolDeJuego(){
    root = nullptr;
    this->despleG = nullptr;
    valorCorrecto = -1;
    valorIncorrecto = NOHAYINCORRECTO;
    _siz = 0;
    _nivelActual = -1;
}

template<typename T>
ArbolDeJuego<T>::Nodo::Nodo(){
    valor = -10000;
    nivel = 0;
    padre = nullptr;
}

template<typename T>
ArbolDeJuego<T>::~ArbolDeJuego(){
    if(root) root->destruirme();
}

template<typename T>
ArbolDeJuego<T>::Nodo::Nodo(T p, int valor, int nivel){
    puz = p;
    this->valor = valor;
    this->nivel = nivel;
    padre = nullptr;
}

#endif // ARBOLDEJUEGO_H
