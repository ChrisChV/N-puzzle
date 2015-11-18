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

void desple(Puzzle actual, list<tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto,int valorActual,bool flag);



class Puzzle
{
    public:
        class Square{
            public:
                Square();
                Square(int,int,int,int,string);
                virtual ~Square(){};
                bool operator!=(Square second){
                    if(fil == second.fil and col == second.col and valor == second.valor and n == second.n and image == second.image)return false;
                    return true;
                };
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
        Puzzle(int**,int,string);
        Puzzle(map<int,map<int,Square>>,string,int,int,int);
        bool operator==(Puzzle second){
            //cout<<"fffff"<<endl;
            for(int i = 1; i <= matriz.size(); i++){
                for(int j = 1; j <= matriz.size(); j++){
                    if(matriz[i][j].valor != second.matriz[i][j].valor)return false;
                }
            }
            return true;
        };
        bool operator!=(Puzzle second){
            //cout<<"hhhh"<<endl;
            for(int i = 1; i <= matriz.size(); i++){
                for(int j = 1; j <= matriz.size(); j++){
                    if(matriz[i][j].valor != second.matriz[i][j].valor)return true;
                }
            }
            return false;
        };
        bool operator<(Puzzle second){
            if(resuelto < second.resuelto)return true;
            return false;
        }
        bool operator>(Puzzle second){
            if(resuelto < second.resuelto)return true;
            return false;
        }
        void next();
        map<int,map<int,Square>> getMatriz(){return matriz;};
        void print();
        int estaResuelto();
        void Resolver();
        void ResolverUsuario();
        Puzzle copiarPuzzle();
        tuple<int,int> getVacio();
        int getValor(int,int);
        void swapValores(int,int);
        list<Square> getVecinos(int,int,int,int);
        int vacioFil;
        int vacioCol;
        virtual ~Puzzle();
        string name;
        int resuelto;
    protected:
    private:
        map<int,map<int,Square>> matriz;
        ///int getMejorSolucion(list<Square *>, Square *&);
        void nextPorPaso(list<Puzzle>&);
        ArbolDeJuego<Puzzle> juego;
};

void Puzzle::ResolverUsuario(){
    cout<<"COMANDOS:"<<endl;
    cout<<"a  mover el vacio para izquierda"<<endl;
    cout<<"w  mover el vacio para arriba"<<endl;
    cout<<"d  mover el vacio para derecha"<<endl;
    cout<<"s  mover el vacio para abajo"<<endl;
    cout<<"m  guardar el actual en memoria"<<endl;
    cout<<"r  regresar al que esta en memoria"<<endl;
    map<int,map<int,Square>> memoria = matriz;
    int mFil = vacioFil;
    int mCol = vacioCol;
    int mResuleto = resuelto;
    while(resuelto != 1){
        print();
        char t;
        cin>>t;
        int pos = matriz[vacioFil][vacioCol].getPosicion();
        switch(t){
            case 'a':
                if(pos == IZQUIERDA or pos == ARRIBAIZQUIERDA or pos == ABAJOIZQUIERDA){
                    cout<<"No puedes moverte para la Izquierda"<<endl;
                    break;
                }
                resuelto += getValor(vacioFil,vacioCol -1);
                swapValores(vacioFil,vacioCol - 1);

                break;
            case 'w':
                if(pos == ARRIBA or pos == ARRIBADERECHA or pos == ARRIBAIZQUIERDA){
                    cout<<"No puedes moverte para Arriba"<<endl;
                    break;
                }
                resuelto += getValor(vacioFil - 1, vacioCol);
                swapValores(vacioFil - 1, vacioCol);
                break;
            case 'd':
                if(pos == DERECHA or pos == ARRIBADERECHA or pos == ABAJODERECHA){
                    cout<<"No puedes moverte para Derecha"<<endl;
                    break;
                }
                resuelto += getValor(vacioFil, vacioCol + 1);
                swapValores(vacioFil, vacioCol + 1);
                break;
            case 's':
                if(pos == ABAJO or pos == ABAJODERECHA or pos == ABAJOIZQUIERDA){
                    cout<<"No puedes moverte para ABAJO"<<endl;
                    break;
                }
                resuelto += getValor(vacioFil + 1, vacioCol);
                swapValores(vacioFil + 1, vacioCol);
                break;
            case 'm':
                cout<<"GUARDADO"<<endl;
                memoria = matriz;
                mFil = vacioFil;
                mCol = vacioCol;
                mResuleto = resuelto;
                break;
            case 'r':
                cout<<"REGRESANDO"<<endl;
                matriz = memoria;
                vacioFil = mFil;
                vacioCol = mCol;
                resuelto = mResuleto;
                break;
            default:
                cout<<"Escriba uno de los comandos a,w,s o d"<<endl;
                break;
        }
    }
    cout<<"BUENA, LO RESOLVISTE"<<endl;
    print();
}

Puzzle::Puzzle(map<int,map<int,Square>> matriz,string name, int fil,int col, int resuelto){
    this->matriz = matriz;
    this->name = name;
    vacioCol = col;
    vacioFil = fil;
    this->resuelto = resuelto;
}

void Puzzle::swapValores(int fil, int col){
    Square nuevoVacio = matriz[fil][col];
    Square atras = matriz[vacioFil][vacioCol];
    nuevoVacio.fil = vacioFil;
    nuevoVacio.col = vacioCol;
    atras.fil = fil;
    atras.col = col;
    /*
    swap(matriz[fil][col],matriz[vacioFil][vacioCol]);
    matriz[fil][col].fil = fil;
    matriz[fil][col].fil = col;
    matriz[vacioFil][vacioCol].fil = vacioFil;
    matriz[vacioFil][vacioCol].col = vacioCol;
    */
    matriz[vacioFil][vacioCol] = nuevoVacio;
    matriz[fil][col] = atras;
    vacioFil = fil;
    vacioCol = col;
}

int Puzzle::getValor(int fil, int col){
    Square vecino = matriz[fil][col];
    Square vacio = matriz[vacioFil][vacioCol];
    if(vecino.getValorReal() == vecino.valor)return 1;
    if(vacio.getValorReal() == vecino.valor)return -1;
    return 0;
}

tuple<int,int> Puzzle::getVacio(){
    return make_tuple(vacioFil,vacioCol);
}

int Puzzle::estaResuelto(){
    return resuelto;
}

void Puzzle::print(){
    for(int i = 1; i <= matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            cout<<matriz[i][j].valor<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

list<Puzzle::Square> Puzzle::getVecinos(int filS, int colS, int filAnterior, int colAnterior){
    Square s  = matriz[filS][colS];
    //cout<<"FIL->"<<s.fil<<endl;
    //cout<<"COL->"<<s.col<<endl;
    Square anterior;
    bool flag;
    if(filAnterior == -1 or colAnterior == -1)flag = false;
    else{
        anterior = matriz[filAnterior][colAnterior];
        flag = true;
    }
    int pos = s.getPosicion();
    list<Square> vecinos;
    switch(pos){
        case ARRIBAIZQUIERDA:
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case ARRIBA:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case ARRIBADERECHA:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case DERECHA:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case ABAJODERECHA:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            break;
        case ABAJO:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            break;
        case ABAJOIZQUIERDA:
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            break;
        case IZQUIERDA:
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case CENTRO:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
    }
    return vecinos;
}

/*
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
*/

void Puzzle::Resolver(){
    cout<<"Tablero al inicio"<<endl;
    cout<<"Nivel->"<<juego.nivel()<<endl;
    cout<<"Size->"<<juego.size()<<endl;
    print();
    list<Puzzle> camino;
    while(!juego.desplegar(camino,resuelto)){
        camino.clear();
    }
    nextPorPaso(camino);
}

void Puzzle::nextPorPaso(list<Puzzle>& camino){
    cout<<"ENCONTRO CAMINO"<<endl<<endl;
    for(Puzzle p : camino){
        matriz = p.getMatriz();
        ///Lentearlo;
        cout<<"NEXT"<<endl;
        print();
        vacioFil = p.vacioFil;
        vacioCol = p.vacioCol;
    }
}

void Puzzle::next(){
    list<Puzzle> camino;
    while(!juego.desplegar(camino,resuelto)){
        camino.clear();
    }
    nextPorPaso(camino);
    cout<<"ACTUAAAAAAAAAAAAAAAAAALLLLLLLLL"<<endl;
    cout<<"RESUELTO->"<<resuelto<<endl;
    print();
    char t;
    cin>>t;
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

Puzzle::Puzzle(int **m,int n,string name){
    void (*des)(Puzzle, list<tuple<int,Puzzle>>&, Puzzle, int,int,bool);
    des = desple;
    juego = ArbolDeJuego<Puzzle>(-1,1,des,n*n);
    this->name = name;
    resuelto = 0;
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n; j++){
            matriz[i+1][j+1] = Square(i+1,j+1,m[i][j],n,name);
            if(m[i][j] == n*n){
                vacioFil = i+1;
                vacioCol = j+1;
            }
            if(m[i][j] != matriz[i+1][j+1].getValorReal()) resuelto++;
        }
    }
    Puzzle nuevo(matriz,name,vacioFil,vacioCol,resuelto);
    juego.insert(nuevo,resuelto);
    cout<<"hola"<<endl;
}

Puzzle::Puzzle(int n, string name){
    void (*des)(Puzzle, list<tuple<int,Puzzle>>&, Puzzle, int,int,bool);
    des = desple;
    juego = ArbolDeJuego<Puzzle>(-1,1,des,n*n);
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
            matriz[i][j] = Square(i,j,numero,n,name);
            if(numero == n * n){
               vacioFil = i;
               vacioCol = j;
            }
            if(numero != matriz[i][j].getValorReal()) resuelto++;
            valores.erase(valores.begin() + h);
        }
    }
    Puzzle nuevo(matriz,name,vacioFil,vacioCol,resuelto);
    juego.insert(nuevo,resuelto);
    cout<<"hola"<<endl;
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
    image = "noHayImagen";
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
   /* for(int i = 1; i <= matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            delete matriz[i][j];
        }
    }
    */
}



void desple(Puzzle actual, list<tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto, int valorActual,bool flag){
    int filAnte;
    int colAnte;
    if(!flag){
        filAnte = -1;
        colAnte = -1;
    }
    else{
        filAnte = anterior.vacioFil;
        colAnte = anterior.vacioCol;
    }
    list<Puzzle::Square> vecinos = actual.getVecinos(actual.vacioFil,actual.vacioCol,filAnte,colAnte);

    Puzzle temp = actual;
    //cout<<"DESPLEGANDO"<<endl<<endl;
    //actual.print();

    for(Puzzle::Square s : vecinos){
        //cout<<"VECINO->"<<s.valor<<endl;
        actual = temp;
        int valor =  valorActual + actual.getValor(s.fil,s.col);
            if(actual.getValor(s.fil,s.col) != valorActual){
            actual.swapValores(s.fil,s.col);
            //cout<<"DESPLIEGUE"<<endl<<endl;
            //actual.print();
            resultado.push_back(make_tuple(valor,actual));
        }
    }
}


#endif // PUZZLE_H
