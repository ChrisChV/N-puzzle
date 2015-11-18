#ifndef ARBOLDEJUEGO_H
#define ARBOLDEJUEGO_H
#include "list"
#include "tuple"
#include "FibonacciHeap.h"

#define NOHAYINCORRECTO 1000;


template<typename T>
class ArbolDeJuego
{
    public:
        class Nodo{
            public:
                Nodo();
                Nodo(T, int,int);
                T puz;
                std::list<Nodo *> hijos;
                Nodo * padre;
                int valor;
                int nivel;
                int cod;
                void destruirme();
        };
        class NodoDTO{
            public:
                NodoDTO(){nodo = nullptr;};
                NodoDTO(Nodo * n){nodo = n;};
                bool operator==(NodoDTO second){
                    if(nodo->cod == second.nodo->cod)return true;
                    return false;
                }
                bool operator!=(NodoDTO second){
                    if(nodo->cod != second.nodo->cod)return true;
                    return false;
                }
                bool operator <(NodoDTO second){
                    if(nodo->valor < second.nodo->valor)return true;
                    return false;
                }
                bool operator>(NodoDTO second){
                    if(nodo->valor > second.nodo->valor)return true;
                    return false;
                }
                Nodo * nodo;
        };
        ArbolDeJuego();
        ArbolDeJuego(int valorC,int, void (*despleG)(T,std::list<std::tuple<int,T>>&,T,int,int,bool),int);
        int desplegar(std::list<T>&,int&);
        void insert(T puz,int valor);
        int size(){return _siz;};
        int nivel(){return _nivelActual;};
        bool haceBucle(Nodo * nodo);
        void (*print)(T);
        void clear();
        virtual ~ArbolDeJuego();
    protected:
    private:
        Nodo * root;
        Nodo * actual;
        Nodo * mejor;
        Nodo * anteriorMejor;
        int nMejor;
        int _siz;
        int _nivelActual;
        int valorCorrecto;
        int valorIncorrecto;
        int valorIncorrectoTemp;
        int _revisadosNivel;
        bool bloqueado;
        bool entroEnBucle;
        int contadorDeBucle;
        int ordenDeEleccion;
        int _ordenDeEleccion;
        int bloqueados;
        int codActual;
        int desbloqueosActuales;
        std::list<Nodo *> ultimaFila;
        FibonacciHeap<NodoDTO> heap;
        std::list<Nodo *> filaAnterior;
        void _insert(T,T);
        void (*despleG)(T,std::list<std::tuple<int,T>>&,T,int,int,bool);
        int _desplegar(Nodo *& elegido);

};

template<typename T>
bool ArbolDeJuego<T>::haceBucle(Nodo * nodo){
    Nodo * padre = nodo->padre;
    while(padre){
        if(nodo->puz == padre->puz)return true;
        padre = padre->padre;
        //std::cout<<"hola"<<std::endl;
    }
    return false;
}

template<typename T>
void ArbolDeJuego<T>::_insert(T anterior,T elegido){
    root = new Nodo(anterior,-1000,0);
    actual = new Nodo(elegido,-1000,1);
    root->hijos.push_back(actual);
    _siz = 2;
    _nivelActual = 1;
}

template<typename T>
int ArbolDeJuego<T>::desplegar(std::list<T>& camino,int &resuelto){
    Nodo * elegido;
    _revisadosNivel = 0;
    /*
    if(contadorDeBucle == 4){
        contadorDeBucle = 0;
        ordenDeEleccion++;
        cout<<"BUCLEEEE!!!!!!!!!!!->"<<ordenDeEleccion<<endl;
        _ordenDeEleccion = ordenDeEleccion;
        clear();
        _insert(anteriorMejor->puz,mejor->puz);
    }
    if(bloqueado){
        _nivelActual--;
        valorIncorrecto = NOHAYINCORRECTO;
        desbloqueosActuales++;
        bloqueado = false;
    }
    else{
        valorIncorrecto = valorIncorrectoTemp;
    }
    */
    bloqueados = 0;
    _revisadosNivel = 0;
    int t = _desplegar(elegido);
    if(t == -1){
        return -1;
    }
    else if(t == 1){
        while(elegido != this->actual){
            camino.push_back(elegido->puz);
            elegido = elegido->padre;
        }
        camino.reverse();
        return true;
    }

    return false;
}

template<typename T>
int ArbolDeJuego<T>::_desplegar(Nodo *& elegido){
        if(heap.empty()){
            return -1;
        }
        Nodo * actual = heap.popMin().nodo;
        std::cout<<"NIVELACTUAL->"<<actual->nivel<<std::endl;
        std::cout<<"MENOR->"<<actual->valor<<std::endl;
        std::cout<<"ACTUAL->"<<std::endl;
        //print(actual->puz);
        //char t;
        //std::cin>>t;
        std::list<std::tuple<int,T>> hijos;
        T ele;
        T anterior;
        std::cout<<"NIVEL->"<<actual->nivel<<std::endl;
        bool flag = false;
        if(actual->padre){
            anterior = actual->padre->puz;
            flag = true;
        }
        despleG(actual->puz,hijos,anterior,valorIncorrecto,actual->valor,flag);
        _revisadosNivel++;
        //cout<<"SIZE->"<<hijos.size()<<endl;
        if(hijos.empty()){
            bloqueados++;
        }
        std::list<Nodo *>temp;
        for(auto t : hijos){
            Nodo * nuevo = new Nodo(std::get<1>(t),std::get<0>(t), actual->nivel + 1);
            ///std::cout<<"HIJO->"<<nuevo->valor<<std::endl;

            //print(nuevo->puz);
            //char s;
            //std::cin>>s;
            nuevo->cod = codActual;
            codActual++;
            //cout<<"RESULTADO->"<<nuevo->valor<<endl;
            nuevo->padre = actual;
            actual->hijos.push_back(nuevo);
            if(!haceBucle(nuevo)){
                if(temp.empty() or temp.front()->valor > nuevo->valor){
                    temp.clear();
                    temp.push_back(nuevo);
                }
                else if(temp.front()->valor == nuevo->valor){
                    temp.push_back(nuevo);
                }
                if(nuevo->valor == 0){
                    elegido = nuevo;
                    return true;
                }
            }

        }
        for(Nodo * n : temp){
            heap.insert(NodoDTO(n));
        }

        _siz += actual->hijos.size();
    ///_nivelActual++;
    return false;
}

template<typename T>
void ArbolDeJuego<T>::clear(){
    //if(root) root->destruirme();
    root = nullptr;
    actual = nullptr;
    _siz = 0;
    _nivelActual = -1;
}

template<typename T>
void ArbolDeJuego<T>::insert(T puz,int valor){
    if(!root){
        Nodo * nuevo = new Nodo(puz,valor,0);
        nuevo->cod = codActual;
        heap.insert(NodoDTO(nuevo));
        codActual++;
        ultimaFila.push_back(nuevo);
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
ArbolDeJuego<T>::ArbolDeJuego(int valorC,int valorI, void (*despleG)(T,std::list<std::tuple<int,T>>&,T,int,int,bool),int n){
    root = nullptr;
    bloqueado = false;
    entroEnBucle = false;
    this->despleG = despleG;
    codActual = 0;
    contadorDeBucle = 0;
    nMejor = n + 1;
    desbloqueosActuales = 0;
    ordenDeEleccion = 1;
    _ordenDeEleccion = 1;
    valorCorrecto = valorC;
    valorIncorrecto = valorI;
    valorIncorrectoTemp = valorI;
    _siz = 0;
    _nivelActual = -1;
}

template<typename T>
ArbolDeJuego<T>::ArbolDeJuego(){
    root = nullptr;
    bloqueado = false;
    codActual = 0;
    this->despleG = nullptr;
    entroEnBucle = false;
    desbloqueosActuales = 0;
    contadorDeBucle = 0;
    ordenDeEleccion = 1;
    nMejor = NOHAYINCORRECTO;
    _ordenDeEleccion = 1;
    valorCorrecto = -1;
    valorIncorrecto = NOHAYINCORRECTO;
    valorIncorrectoTemp = NOHAYINCORRECTO;
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
