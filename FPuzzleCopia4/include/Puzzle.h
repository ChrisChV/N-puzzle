#ifndef PUZZLE_H
#define PUZZLE_H
#include "stdlib.h"
#include "list"
#include "algorithm"
#include "vector"
#include "map"
#include "ArbolDeJuego.h"
#include <allegro.h>
#include "math.h"

#define ANCHO_VENTANA 1000
#define ALTO_VENTANA 800
#define SOLUCION 0

//using namespace std;

#define INTERLINEADO 3

enum Posiciones{IZQUIERDA,ARRIBA,DERECHA,ABAJO,ARRIBAIZQUIERDA,ARRIBADERECHA,ABAJODERECHA,ABAJOIZQUIERDA,CENTRO,NOESVECINO};

class Puzzle;

void desple(Puzzle actual, std::list<std::tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto,int valorActual,bool flag);

void pri(Puzzle puz);

class Puzzle
{
    public:
        class Square{
            public:
                Square();
                Square(int,int,int,int,std::string,int,int);
                Square(int fil,int col, int val,int n);
                virtual ~Square(){};
                bool operator!=(Square second){
                    if(fil == second.fil and col == second.col and valor == second.valor and n == second.n and image == second.image)return false;
                    return true;
                };
                void _llenarValores(int,int,int,int,std::string);
                int getValorReal();
                int getPosicion();
                void dibujar(BITMAP *);
                Square * vecinos[4];
                void destruir();
                int getVecino(int);
                void _distanciaManhatan(int &,std::map<int,Square>&);
                int fil;
                int col;
                int valor;
                int X;
                int Y;
                int n;
                int distanciaM;
                std::string image;
                BITMAP * imagen;
        };
        Puzzle();///
        Puzzle(int,std::string,BITMAP *,std::string);//;
        Puzzle(int**,int,std::string,BITMAP *,std::string);//;
        Puzzle(std::map<int,Square>,std::string,int,int,BITMAP * buffer,BITMAP *,int);///
        Puzzle(std::map<int,Square>, std::map<int,Square>& goal, int,int);
        void destruir();///
        bool operator==(Puzzle second){
            //cout<<"fffff"<<endl;
            for(int i = 1; i <= matriz.size(); i++){
                if(matriz[i].col != second.matriz[i].col or matriz[i].fil != second.matriz[i].fil)return false;
            }
            return true;
        };
        void next();///
        std::map<int,Square> getMatriz(){return matriz;};///
        void print();///
        int estaResuelto();///
        void Resolver();///
        void ResolverUsuario();///
        void swapValores(int);///
        std::list<std::tuple<int,Square>> getVecinos(int);///
        int vacio;
        BITMAP * image;
        BITMAP * buffer;
        std::list<Puzzle>::iterator actual;
        void dibujar();
        std::map<int,Square> goal;
        virtual ~Puzzle();
        std::string name;
        std::list<Puzzle> camino;
        int distanciaManhatan;
        void distanciaM();
        std::map<int,Square> matriz;
    protected:
    private:

        ///int getMejorSolucion(list<Square *>, Square *&);
        void nextPorPaso(std::list<Puzzle>&);
        ArbolDeJuego<Puzzle> juego;
};

void Puzzle::distanciaM(){
    for(int i = 1; i <= matriz.size(); i++){
        if(i != vacio)matriz[i]._distanciaManhatan(distanciaManhatan,goal);
    }
}

Puzzle::Puzzle(std::map<int,Square> matriz,std::map<int,Square>& goal,int vacio,int distanciaManhatan){
    this->matriz = matriz;
    this->vacio = vacio;
    this->distanciaManhatan = distanciaManhatan;
    image = nullptr;
    buffer = nullptr;
    this->goal = goal;
    name = "default";
}

int Puzzle::Square::getVecino(int ves){
    for(int i = 0; i < 4; i++){
        if(vecinos[i]){
            if(vecinos[i]->valor == ves)return i;
        }
    }
    return NOESVECINO;
}

void Puzzle::Square::_distanciaManhatan(int &disM, std::map<int,Square> &goal){
    disM -= distanciaM;
    distanciaM = std::abs(fil - goal[valor].fil) + std::abs(col - goal[valor].col);
    disM += distanciaM;
}

void Puzzle::Square::destruir(){
    destroy_bitmap(imagen);
}

void Puzzle::destruir(){
    std::string rm = "rm -R " + name + "/";
    system(rm.c_str());
    for(int i = 1; i < matriz.size(); i++){
        matriz[i].destruir();
    }
}

void Puzzle::Square::dibujar(BITMAP * buffer){
    draw_sprite(buffer,imagen,X,Y);
}

void Puzzle::dibujar(){
    clear_to_color(buffer, 0x999999);
    for(int i = 1; i <=matriz.size(); i++){
            if(matriz[i].valor != matriz[i].n * matriz[i].n) matriz[i].dibujar(buffer);
    }
    blit(buffer,screen,0,0,0,0,ANCHO_VENTANA,ALTO_VENTANA);
}


void Puzzle::ResolverUsuario(){
    std::cout<<"COMANDOS:"<<std::endl;
    std::cout<<"a  mover el vacio para izquierda"<<std::endl;
    std::cout<<"w  mover el vacio para arriba"<<std::endl;
    std::cout<<"d  mover el vacio para derecha"<<std::endl;
    std::cout<<"s  mover el vacio para abajo"<<std::endl;
    std::cout<<"m  guardar el actual en memoria"<<std::endl;
    std::cout<<"r  regresar al que esta en memoria"<<std::endl;
    std::map<int,Square> memoria = matriz;
    int mResuleto = distanciaManhatan;
    std::cout<<"DISManhatan->"<<distanciaManhatan<<std::endl;
    while(distanciaManhatan != 0){
        print();
        std::cout<<"VACIOFIL->"<<matriz[vacio].fil<<std::endl;
        std::cout<<"VACIOCOL->"<<matriz[vacio].col<<std::endl;
        for(int i = 0; i < 4; i++){
            if(matriz[vacio].vecinos[i]){
                std::cout<<"VECINOFIL"<<i<<"->"<<matriz[vacio].vecinos[i]->fil<<std::endl;
                std::cout<<"VECINOCOL"<<i<<"->"<<matriz[vacio].vecinos[i]->col<<std::endl;
            }
        }
        char t;
        std::cin>>t;
        int pos = matriz[vacio].getPosicion();
        switch(t){
            case 'a':
                if(pos == IZQUIERDA or pos == ARRIBAIZQUIERDA or pos == ABAJOIZQUIERDA){
                    std::cout<<"No puedes moverte para la Izquierda"<<std::endl;
                    break;
                }
                swapValores(matriz[vacio].vecinos[IZQUIERDA]->valor);
                dibujar();
                break;
            case 'w':
                if(pos == ARRIBA or pos == ARRIBADERECHA or pos == ARRIBAIZQUIERDA){
                    std::cout<<"No puedes moverte para Arriba"<<std::endl;
                    break;
                }
                swapValores(matriz[vacio].vecinos[ARRIBA]->valor);
                dibujar();
                break;
            case 'd':
                if(pos == DERECHA or pos == ARRIBADERECHA or pos == ABAJODERECHA){
                    std::cout<<"No puedes moverte para Derecha"<<std::endl;
                    break;
                }
                std::cout<<"M->"<<matriz[vacio].valor<<std::endl;
                if(!matriz[vacio].vecinos[DERECHA]) std::cout<<"VECINOOOOOOO"<<std::endl;

                swapValores(matriz[vacio].vecinos[DERECHA]->valor);
                dibujar();
                break;
            case 's':
                if(pos == ABAJO or pos == ABAJODERECHA or pos == ABAJOIZQUIERDA){
                    std::cout<<"No puedes moverte para ABAJO"<<std::endl;
                    break;
                }
                swapValores(matriz[vacio].vecinos[ABAJO]->valor);
                dibujar();
                break;
            case 'm':
                std::cout<<"GUARDADO"<<std::endl;
                memoria = matriz;
                mResuleto = distanciaManhatan;
                break;
            case 'r':
                std::cout<<"REGRESANDO"<<std::endl;
                matriz = memoria;
                distanciaManhatan = mResuleto;
                break;
            default:
                std::cout<<"Escriba uno de los comandos a,w,s o d"<<std::endl;
                break;
        }
    }
    std::cout<<"BUENA, LO RESOLVISTE"<<std::endl;
    print();
}

Puzzle::Puzzle(std::map<int,Square> matriz,std::string name, int vas, int distanciaManhatan,BITMAP * buffer,BITMAP * imagen,int i){
    this->matriz = matriz;
    this->name = name;
    image = imagen;
    vacio = vas;
    this->distanciaManhatan = distanciaManhatan;
    this->buffer = buffer;
}

void Puzzle::swapValores(int valor){

    Square nuevoVacio = matriz[valor];
    Square atras = matriz[vacio];
    int tempX = nuevoVacio.X;
    int tempY = nuevoVacio.Y;
    int tempFil = nuevoVacio.fil;
    int tempCol = nuevoVacio.col;
    nuevoVacio.X = atras.X;
    nuevoVacio.Y = atras.Y;
    nuevoVacio.fil = atras.fil;
    nuevoVacio.col = atras.col;
    atras.fil = tempFil;
    atras.col = tempCol;
    atras.X = tempX;
    atras.Y = tempY;

    int pos = matriz[vacio].getVecino(valor);
    auto izq = nuevoVacio.vecinos[IZQUIERDA];
    auto arr = nuevoVacio.vecinos[ARRIBA];
    auto der = nuevoVacio.vecinos[DERECHA];
    auto abj = nuevoVacio.vecinos[ABAJO];
    nuevoVacio.vecinos[IZQUIERDA] = atras.vecinos[IZQUIERDA];
    nuevoVacio.vecinos[ARRIBA] = atras.vecinos[ARRIBA];
    nuevoVacio.vecinos[DERECHA] = atras.vecinos[DERECHA];
    nuevoVacio.vecinos[ABAJO] = atras.vecinos[ABAJO];
    atras.vecinos[IZQUIERDA] = izq;
    atras.vecinos[ARRIBA] = arr;
    atras.vecinos[DERECHA] = der;
    atras.vecinos[ABAJO] = abj;

    nuevoVacio._distanciaManhatan(distanciaManhatan,goal);
    Square * t = nullptr;
    Square * tt = nullptr;
    switch(pos){
        case IZQUIERDA:
            t = atras.vecinos[DERECHA];
            tt = nuevoVacio.vecinos[IZQUIERDA];
            atras.vecinos[DERECHA] = nuevoVacio.vecinos[IZQUIERDA];
            nuevoVacio.vecinos[IZQUIERDA] = t;
            break;
        case ARRIBA:
            t = atras.vecinos[ABAJO];
            tt = nuevoVacio.vecinos[ARRIBA];
            atras.vecinos[ABAJO] = nuevoVacio.vecinos[ARRIBA];
            nuevoVacio.vecinos[ARRIBA] = t;
            break;
        case DERECHA:
            t = atras.vecinos[IZQUIERDA];
            tt = nuevoVacio.vecinos[DERECHA];
            atras.vecinos[IZQUIERDA] = nuevoVacio.vecinos[DERECHA];
            nuevoVacio.vecinos[DERECHA] = t;
            break;
        case ABAJO:
            t = atras.vecinos[ARRIBA];
            tt = nuevoVacio.vecinos[ABAJO];
            atras.vecinos[ARRIBA] = nuevoVacio.vecinos[ABAJO];
            nuevoVacio.vecinos[ABAJO] = t;
            break;
    }
    /*
    swap(matriz[fil][col],matriz[vacioFil][vacioCol]);
    matriz[fil][col].fil = fil;
    matriz[fil][col].fil = col;
    matriz[vacioFil][vacioCol].fil = vacioFil;
    matriz[vacioFil][vacioCol].col = vacioCol;
    */
    for(int i = 0; i < 4; i++){
        if(nuevoVacio.vecinos[i] and nuevoVacio.vecinos[i]->valor != vacio){
            nuevoVacio.vecinos[i]->vecinos[nuevoVacio.vecinos[i]->getVecino(vacio)] = tt;
        }
        if(atras.vecinos[i] and atras.vecinos[i]->valor != valor){
            //std::cout<<"VECINOVECINO3->"<<atras.vecinos[i]->valor<<std::endl;
            atras.vecinos[i]->vecinos[atras.vecinos[i]->getVecino(valor)] = t;
        }
    }

    matriz[valor] = nuevoVacio;
    matriz[vacio] = atras;
}

int Puzzle::estaResuelto(){
    return distanciaManhatan;
}

void Puzzle::print(){
    std::map<int,std::map<int,int>> tempM;
    for(int i = 1; i <= matriz.size(); i++){
        tempM[matriz[i].fil][matriz[i].col] = matriz[i].valor;
    }
    for(int i = 1; i <= tempM.size(); i++){
        for(int j = 1; j <= tempM.size(); j++){
            std::cout<<tempM[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

/*
std::list<Puzzle::Square> Puzzle::getVecinos(int ant){
    Square s  = matriz[vacio];
    //cout<<"FIL->"<<s.fil<<endl;
    //cout<<"COL->"<<s.col<<endl;
    Square anterior;
    bool flag;
    if(ant == -1)flag = false;
    else{
        anterior = matriz[ant];
        flag = true;
    }
    int pos = s.getPosicion();
    std::list<Square> vecinos;
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
*/

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
    std::cout<<"Tablero al inicio"<<std::endl;
    std::cout<<"Nivel->"<<juego.nivel()<<std::endl;
    std::cout<<"Size->"<<juego.size()<<std::endl;
    print();
    int t;
    while(true){
        int t = juego.desplegar(camino,distanciaManhatan);
        if(t == -1){
            std::cout<<"EL PUZZLE NO TIENE SOLUCION :("<<std::endl;
            break;
        }
        else if(t == 1)break;
        camino.clear();
    }
    if(t != -1){
        camino.push_front(Puzzle(matriz,goal,vacio, distanciaManhatan));
        actual = camino.begin();
        nextPorPaso(camino);
    }
}

void Puzzle::nextPorPaso(std::list<Puzzle>& camino){
    std::cout<<"ENCONTRO CAMINO"<<std::endl<<std::endl;
    auto i = camino.end();
    i--;
    while(actual != i){
        next();
    }

}

void Puzzle::next(){
    auto i = camino.end();
    i--;
    if(actual == i){
        std::cout<<"Ya no hay next"<<std::endl;
        return;
    }
    std::cout<<"NEXT"<<std::endl;
    actual++;
    matriz = (*actual).getMatriz();
    //for(int i = 0 ; i < 100000000; i++){};
    //dibujar();
    print();
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

Puzzle::Puzzle(int **m,int n,std::string name, BITMAP * buffer,std::string extension){
    void (*des)(Puzzle, std::list<std::tuple<int,Puzzle>>&, Puzzle, int,int,bool);
    des = desple;
    juego = ArbolDeJuego<Puzzle>(-1,1,des,n*n);
    void(*p)(Puzzle);
    p = pri;
    juego.print = p;
    this->buffer = buffer;
    this->name = name;
    std::string file = name + extension;
    std::string file2 = name +".pcx";
    std::string convert = "convert "+ file + " " + file2;
    system(convert.c_str());
    std::string dir = "mkdir " + name;
    std::string cp = "mv " + file2 + " " + name + "/";
    system(dir.c_str());
    system(cp.c_str());
    file = name + "/" + file2;
    image = load_bitmap(file.c_str(),NULL);
    int x = image->w / n;
    std::string sX = std::to_string(x);
    int y = image->h / n;
    std::string sY = std::to_string(y);
    std::string crop = "convert " + file + " -crop "+ sX+ "x"+ sY + " "+ file;
    system(crop.c_str());
    distanciaManhatan = 0;
    vacio = n * n;
    distanciaManhatan = 0;
    int altoImagen  = image->h;
    int anchoImagen = image->w;
    int posY = (ALTO_VENTANA - (altoImagen + INTERLINEADO * n)) / 2;
    int posX = (ANCHO_VENTANA - (anchoImagen + INTERLINEADO * n)) / 2;
    int tempX = posX;

    std::vector<std::vector<Square *>> vec;
    std::map<int,Square> mGoal;
    for(int i = 0; i < n;i++){
        std::vector<Square *> v;
        for(int j = 0; j < n; j++){
            std::string sN  = std::to_string(m[i][j] - 1);
            std::string img = name + "/" + name + "-" + sN+ ".pcx";
            Square nuevo(i+1,j+1,m[i][j],n,img,posX,posY);
            matriz[m[i][j]] = nuevo;
            posX += x + INTERLINEADO;
            v.push_back(&(matriz[m[i][j]]));
            mGoal[nuevo.getValorReal()] = Square(i+1,j+1,nuevo.getValorReal(),n);
        }
        posY += y + INTERLINEADO;
        posX = tempX;
        vec.push_back(v);
    }
    goal = mGoal;
    distanciaM();
    std::cout<<"SIZE->"<<vec.size()<<std::endl;
    for(int i = 0; i < vec.size(); i++){
        for(int j = 0; j < vec.size(); j++){
            std::cout<<"SIZE2->"<<vec[i].size()<<std::endl;
            Square * s = vec[i][j];
            int pos = s->getPosicion();
            switch(pos){
                case ARRIBAIZQUIERDA:
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case ARRIBA:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case ARRIBADERECHA:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case DERECHA:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case ABAJODERECHA:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    break;
                case ABAJO:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    break;
                case ABAJOIZQUIERDA:
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    break;
                case IZQUIERDA:
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case CENTRO:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;

            }
        }
    }
    Puzzle nuevo(matriz,goal,vacio,distanciaManhatan);
    juego.insert(nuevo,distanciaManhatan);
    std::cout<<"hola"<<std::endl;
}

Puzzle::Puzzle(int n, std::string name,BITMAP * buffer, std::string extension){
    void (*des)(Puzzle, std::list<std::tuple<int,Puzzle>>&, Puzzle, int,int,bool);
    des = desple;
    juego = ArbolDeJuego<Puzzle>(-1,1,des,n*n);
    void(*p)(Puzzle);
    p = pri;
    juego.print = p;
    distanciaManhatan = 0;
    this->buffer = buffer;
    this->name = name;
    std::string file = name + extension;
    std::string file2 = name +".pcx";
    std::string convert = "convert "+ file + " " + file2;
    system(convert.c_str());
    std::string dir = "mkdir " + name;
    std::string cp = "mv " + file2 + " " + name + "/";
    system(dir.c_str());
    system(cp.c_str());
    file = name + "/" + file2;
    image = load_bitmap(file.c_str(),NULL);
    int x = image->w / n;
    std::string sX = std::to_string(x);
    int y = image->h / n;
    std::string sY = std::to_string(y);
    std::string crop = "convert " + file + " -crop "+ sX+ "x"+ sY + " "+ file;
    system(crop.c_str());
    std::vector<int> valores;
    int altoImagen  = image->h;
    int anchoImagen = image->w;
    int posY = (ALTO_VENTANA - (altoImagen + INTERLINEADO * n)) / 2;
    int posX = (ANCHO_VENTANA - (anchoImagen + INTERLINEADO * n)) / 2;
    int tempX = posX;
    vacio = n * n;
    distanciaManhatan = 0;
    std::vector<std::vector<Square *>> vec;
    for(int i = 1; i <= n * n; i++){
        valores.push_back(i);
    }
    std::map<int,Square> mGoal;
    for(int i = 1; i <= n; i++){
        if(valores.empty())break;
        std::vector<Square *> v;
        for(int j = 1; j <= n; j++){
            int h = rand() % valores.size();
            int numero = valores[h];
            std::string sN = std::to_string(numero - 1);
            std::string img = name + "/" + name + "-" + sN+ ".pcx";
            Square nuevo(i,j,numero,n,img,posX,posY);
            matriz[numero] = nuevo;
            v.push_back(&(matriz[numero]));
            posX += x + INTERLINEADO;
            valores.erase(valores.begin() + h);
            mGoal[nuevo.getValorReal()] = Square(i+1,j+1,nuevo.getValorReal(),n);
        }
        posY += y + INTERLINEADO;
        posX = tempX;
        vec.push_back(v);
    }
    goal = mGoal;
    distanciaM();
    for(int i = 0; i < vec.size(); i++){
        for(int j = 0; j < vec.size(); j++){
            Square *s = vec[i][j];
            int pos = s->getPosicion();
            switch(pos){
                case ARRIBAIZQUIERDA:
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case ARRIBA:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case ARRIBADERECHA:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case DERECHA:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case ABAJODERECHA:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    break;
                case ABAJO:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    break;
                case ABAJOIZQUIERDA:
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    break;
                case IZQUIERDA:
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
                case CENTRO:
                    s->vecinos[IZQUIERDA] = vec[i][j - 1];
                    s->vecinos[ARRIBA] = vec[i - 1][j];
                    s->vecinos[DERECHA] = vec[i][j + 1];
                    s->vecinos[ABAJO] = vec[i + 1][j];
                    break;
            }
        }
    }
    Puzzle nuevo(matriz,goal,vacio,distanciaManhatan);
    juego.insert(nuevo,distanciaManhatan);
    std::cout<<"hola"<<std::endl;
}

Puzzle::Puzzle(){
    name = "default";
}

int Puzzle::Square::getValorReal(){
    return n * (fil - 1) + col;
}

void Puzzle::Square::_llenarValores(int fil, int col , int val, int n, std::string img){
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
    imagen = nullptr;
    distanciaM = 0;
    vecinos[IZQUIERDA] = nullptr;
    vecinos[ARRIBA] = nullptr;
    vecinos[DERECHA] = nullptr;
    vecinos[ABAJO] = nullptr;
}

Puzzle::Square::Square(int fil,int col, int val,int n){
    this->fil = fil;
    this->col = col;
    valor = val;
    image = "default";
    imagen = nullptr;
    distanciaM = 0;
}

Puzzle::Square::Square(int fil, int col, int val,int n, std::string img,int X, int Y ){
    this->fil = fil;
    this->col = col;
    this->n = n;
    valor = val;
    image = img;
    imagen = load_bitmap(img.c_str(),NULL);
    this->X = X;
    this->Y = Y;
    distanciaM = 0;
    vecinos[IZQUIERDA] = nullptr;
    vecinos[ARRIBA] = nullptr;
    vecinos[DERECHA] = nullptr;
    vecinos[ABAJO] = nullptr;
}

Puzzle::~Puzzle(){
   /* for(int i = 1; i <= matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            delete matriz[i][j];
        }
    }
    */
}



void desple(Puzzle actual, std::list<std::tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto, int valorActual,bool flag){
    /*
    int filAnte;
    int colAnte;
    if(anterior.name == "default"){
        filAnte = -1;
        colAnte = -1;
    }
    else{
        filAnte = anterior.vacioFil;
        colAnte = anterior.vacioCol;
    }
    */
    //std::list<Puzzle::Square> vecinos = actual.getVecinos(actual.vacioFil,actual.vacioCol,filAnte,colAnte);
    Puzzle temp = actual;
    //cout<<"DESPLEGANDO"<<endl<<endl;
    //actual.print();

    std::list<Puzzle::Square> vecinos;
            std::cout<<"ANTERIROVACIOFIL->"<<anterior.matriz[anterior.vacio].fil<<std::endl;
            std::cout<<"ANTERIROVACIOCOL->"<<anterior.matriz[anterior.vacio].col<<std::endl;
            std::cout<<"ACTUALVACIOFIL->"<<actual.matriz[actual.vacio].fil<<std::endl;
            std::cout<<"ACTUALVACIOCOL->"<<actual.matriz[actual.vacio].col<<std::endl;

    for(int i = 0; i < 4; i++){
        if(actual.matriz[actual.vacio].vecinos[i]){
            std::cout<<"HOLAAAAAAAAAAAAA"<<std::endl;
            std::cout<<"VALOR->"<<actual.matriz[actual.vacio].vecinos[i]->valor<<std::endl;
            std::cout<<actual.matriz[actual.vacio].vecinos[i]->fil<<std::endl;
            std::cout<<actual.matriz[actual.vacio].vecinos[i]->col<<std::endl;
            if(actual.matriz[actual.vacio].vecinos[i]->fil != anterior.matriz[anterior.vacio].fil and actual.matriz[actual.vacio].vecinos[i]->col != anterior.matriz[anterior.vacio].col){
                std::cout<<"WWWWWWWWWWWWWW"<<std::endl;
            }
        }

        if(actual.matriz[actual.vacio].vecinos[i] and (actual.matriz[actual.vacio].vecinos[i]->fil != anterior.matriz[anterior.vacio].fil or  actual.matriz[actual.vacio].vecinos[i]->col != anterior.matriz[anterior.vacio].col)){
            std::cout<<"ttttttttttttt"<<std::endl;
            vecinos.push_back(*(actual.matriz[actual.vacio].vecinos[i]));
        }
    }
    for(Puzzle::Square s : vecinos){
        static Puzzle nuevo;
        nuevo.distanciaManhatan = actual.distanciaManhatan;
        nuevo.goal = actual.goal;
        nuevo.vacio = actual.vacio;

        std::vector<std::vector<Puzzle::Square *>> vec;
        for(int i = 0; i < s.n; i++){
            std::vector<Puzzle::Square*> v;
            for(int j = 0; j < s.n; j++){
                v.push_back(nullptr);
            }
            vec.push_back(v);
        }
        for(int i = 1; i <= s.n * s.n; i++){
            ///std::cout<<i<<std::endl;
            Puzzle::Square nS;
            nS.fil = actual.matriz[i].fil;
            nS.col = actual.matriz[i].col;
            nS.valor = i;
            nS.n = s.n;
            nS.distanciaM = actual.matriz[i].distanciaM;
            nuevo.matriz[i] = nS;
            vec[nS.fil - 1][nS.col - 1] = &(nuevo.matriz[i]);
        }
        for(int i = 0; i < vec.size(); i++){
            for(int j = 0; j < vec.size(); j++){
                Puzzle::Square * s = vec[i][j];
                if(s == nullptr){
                    std::cout<<"AAAAAAAAAAAAAAA"<<std::endl;
                }
                int pos = s->getPosicion();
                switch(pos){
                    case ARRIBAIZQUIERDA:
                        s->vecinos[DERECHA] = vec[i][j + 1];
                        s->vecinos[ABAJO] = vec[i + 1][j];
                        break;
                    case ARRIBA:
                        s->vecinos[IZQUIERDA] = vec[i][j - 1];
                        s->vecinos[DERECHA] = vec[i][j + 1];
                        s->vecinos[ABAJO] = vec[i + 1][j];
                        break;
                    case ARRIBADERECHA:
                        s->vecinos[IZQUIERDA] = vec[i][j - 1];
                        s->vecinos[ABAJO] = vec[i + 1][j];
                        break;
                    case DERECHA:
                        s->vecinos[IZQUIERDA] = vec[i][j - 1];
                        s->vecinos[ARRIBA] = vec[i - 1][j];
                        s->vecinos[ABAJO] = vec[i + 1][j];
                        break;
                    case ABAJODERECHA:
                        s->vecinos[IZQUIERDA] = vec[i][j - 1];
                        s->vecinos[ARRIBA] = vec[i - 1][j];
                        break;
                    case ABAJO:
                        s->vecinos[IZQUIERDA] = vec[i][j - 1];
                        s->vecinos[ARRIBA] = vec[i - 1][j];
                        s->vecinos[DERECHA] = vec[i][j + 1];
                        break;
                    case ABAJOIZQUIERDA:
                        s->vecinos[ARRIBA] = vec[i - 1][j];
                        s->vecinos[DERECHA] = vec[i][j + 1];
                        break;
                    case IZQUIERDA:
                        s->vecinos[ARRIBA] = vec[i - 1][j];
                        s->vecinos[DERECHA] = vec[i][j + 1];
                        s->vecinos[ABAJO] = vec[i + 1][j];
                        break;
                    case CENTRO:
                        s->vecinos[IZQUIERDA] = vec[i][j - 1];
                        s->vecinos[ARRIBA] = vec[i - 1][j];
                        s->vecinos[DERECHA] = vec[i][j + 1];
                        s->vecinos[ABAJO] = vec[i + 1][j];
                        break;
                }
            }
        }
        //cout<<"VECINO->"<<s.valor<<endl;

        //if(actual.getValor(s.fil,s.col) != valorIncorrecto){
            //int valor =  valorActual + actual.getValor(s.fil,s.col);
                nuevo.swapValores(s.valor);
                //for(int i = 1; i <= s.n * s.n; i++){
                  //  std::cout<<"VALOR->"<<nuevo.matriz[i].valor<<std::endl;
                   // std::cout<<"NUEVOFILA->"<<nuevo.matriz[i].fil<<std::endl;
                   // std::cout<<"NUEVOCOL->"<<nuevo.matriz[i].col<<std::endl;
               // }
                //cout<<"DESPLIEGUE"<<endl<<endl;
                //actual.print();
                resultado.push_back(std::make_tuple(nuevo.distanciaManhatan,nuevo));
        //}
    }
}

void pri(Puzzle puz){
    std::map<int,std::map<int,int>> tempM;
    for(int i = 1; i <= puz.matriz.size(); i++){
        tempM[puz.matriz[i].fil][puz.matriz[i].col] = puz.matriz[i].valor;
    }
    for(int i = 1; i <= tempM.size(); i++){
        for(int j = 1; j <= tempM.size(); j++){
            std::cout<<tempM[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

#endif // PUZZLE_H
