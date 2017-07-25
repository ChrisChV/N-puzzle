#ifndef ARBOLDEJUEGO_H
#define ARBOLDEJUEGO_H
#include "list"
#include "tuple"

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
                void destruirme();
        };
        ArbolDeJuego();
        ArbolDeJuego(int valorC,int, void (*despleG)(T,std::list<std::tuple<int,T>>&,T,int,int),int);
        bool desplegar(std::list<T>&,int&);
        void insert(T puz,int valor);
        int size(){return _siz;};
        int nivel(){return _nivelActual;};
        bool haceBucle(Nodo * nodo);
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
        int desbloqueosActuales;
        std::list<Nodo *> ultimaFila;
        void _insert(T,T);
        void (*despleG)(T,std::list<std::tuple<int,T>>&,T,int,int);
        bool _desplegar(Nodo *& elegido, Nodo * actual);

};

template<typename T>
bool ArbolDeJuego<T>::haceBucle(Nodo * nodo){
    Nodo * padre = nodo->padre;
    while(padre){
        if(nodo->puz  == padre->puz)return true;
        padre = nodo->padre;
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
bool ArbolDeJuego<T>::desplegar(std::list<T>& camino,int &resuelto){
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
    if(_desplegar(elegido,actual)){
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
bool ArbolDeJuego<T>::_desplegar(Nodo *& elegido, Nodo * actual){
    std::list<Nodo *> temp;
    std::cout<<"NIVELACTUAL->"<<_nivelActual<<std::endl;
    std::cout<<"MENOR->"<<nMejor<<std::endl;
    for(Nodo * actual : ultimaFila){

        std::list<std::tuple<int,T>> hijos;
        T ele;
        T anterior;
        if(actual->padre) anterior = actual->padre->puz;
        despleG(actual->puz,hijos,anterior,valorIncorrecto,actual->valor);
        _revisadosNivel++;
        //cout<<"SIZE->"<<hijos.size()<<endl;
        if(hijos.empty()){
            bloqueados++;
        }
        for(auto t : hijos){
            Nodo * nuevo = new Nodo(std::get<1>(t),std::get<0>(t),_nivelActual + 1);
            //cout<<"RESULTADO->"<<nuevo->valor<<endl;
            if(!haceBucle(nuevo)){
                temp.push_back(nuevo);
            }

            nuevo->padre = actual;
            actual->hijos.push_back(nuevo);
            if(nMejor > nuevo->valor){
                nMejor = nuevo->valor;
            }
            if(nuevo->valor == 1){
                elegido = nuevo;
                return true;
            }
        }
        _siz += actual->hijos.size();
    }
    _nivelActual++;
    ultimaFila = temp;
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
ArbolDeJuego<T>::ArbolDeJuego(int valorC,int valorI, void (*despleG)(T,std::list<std::tuple<int,T>>&,T,int,int),int n){
    root = nullptr;
    bloqueado = false;
    entroEnBucle = false;
    this->despleG = despleG;
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
