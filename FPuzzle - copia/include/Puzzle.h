#ifndef PUZZLE_H
#define PUZZLE_H
#include "stdlib.h"
#include "list"
#include "algorithm"
#include "vector"
#include "map"
#include "ArbolDeJuego.h"
#include <allegro.h>

#define ANCHO_VENTANA 1000
#define ALTO_VENTANA 800

//using namespace std;

#define INTERLINEADO 3

enum Posiciones{ARRIBAIZQUIERDA,ARRIBA,ARRIBADERECHA,DERECHA,ABAJODERECHA,ABAJO,ABAJOIZQUIERDA,IZQUIERDA,CENTRO};

class Puzzle;

void desple(Puzzle actual, std::list<std::tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto,int valorActual);

class Puzzle
{
    public:
        class Square{
            public:
                Square();
                Square(int,int,int,int,std::string,int,int);
                virtual ~Square(){};
                bool operator!=(Square second){
                    if(fil == second.fil and col == second.col and valor == second.valor and n == second.n and image == second.image)return false;
                    return true;
                };
                void _llenarValores(int,int,int,int,std::string);
                int getValorReal();
                int getPosicion();
                void dibujar(BITMAP *);
                void destruir();
                int fil;
                int col;
                int valor;
                int X;
                int Y;
                int n;
                std::string image;
                BITMAP * imagen;
        };
        Puzzle();
        Puzzle(int,std::string,BITMAP *,std::string);
        Puzzle(int**,int,std::string,BITMAP *,std::string);
        Puzzle(std::map<int,std::map<int,Square>>,std::string,int,int,int,BITMAP * buffer,BITMAP *);
        void destruir();
        bool operator==(Puzzle second){
            //cout<<"fffff"<<endl;
            for(int i = 1; i <= matriz.size(); i++){
                for(int j = 1; j <= matriz.size(); j++){
                    if(matriz[i][j].valor != second.matriz[i][j].valor)return false;
                }
            }
            return true;
        };
        void next();
        std::map<int,std::map<int,Square>> getMatriz(){return matriz;};
        void print();
        int estaResuelto();
        void Resolver();
        void ResolverUsuario();
        Puzzle copiarPuzzle();
        std::tuple<int,int> getVacio();
        int getValor(int,int);
        void swapValores(int,int);
        std::list<Square> getVecinos(int,int,int,int);
        int vacioFil;
        int vacioCol;
        BITMAP * image;
        BITMAP * buffer;
        std::list<Puzzle>::iterator actual;
        void dibujar();
        virtual ~Puzzle();
        std::string name;
        std::list<Puzzle> camino;
        int distanciaM;
        int distanciaManhatan(Puzzle);
    protected:
    private:
        std::map<int,std::map<int,Square>> matriz;
        ///int getMejorSolucion(list<Square *>, Square *&);
        void nextPorPaso(std::list<Puzzle>&);
        ArbolDeJuego<Puzzle> juego;
};

int Puzzle::distanciaManhatan(Puzzle goal){
    int resultado = 0;
    int n = matriz[1][1].n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){

        }
    }

}

void Puzzle::Square::destruir(){
    destroy_bitmap(imagen);
}

void Puzzle::destruir(){
    std::string rm = "rm -R " + name + "/";
    system(rm.c_str());
    for(int i = 1; i < matriz.size(); i++){
        for(int j = 1; j < matriz.size(); j++){
            matriz[i][j].destruir();
        }
    }

}

void Puzzle::Square::dibujar(BITMAP * buffer){
    draw_sprite(buffer,imagen,X,Y);
}

void Puzzle::dibujar(){
    clear_to_color(buffer, 0x999999);
    for(int i = 1; i <=matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            if(matriz[i][j].valor != matriz[i][j].n * matriz[i][j].n) matriz[i][j].dibujar(buffer);
        }
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
    std::map<int,std::map<int,Square>> memoria = matriz;
    int mFil = vacioFil;
    int mCol = vacioCol;
    int mResuleto = distanciaM;
    while(distanciaM != 1){
        print();
        char t;
        std::cin>>t;
        int pos = matriz[vacioFil][vacioCol].getPosicion();
        switch(t){
            case 'a':
                if(pos == IZQUIERDA or pos == ARRIBAIZQUIERDA or pos == ABAJOIZQUIERDA){
                    std::cout<<"No puedes moverte para la Izquierda"<<std::endl;
                    break;
                }
                distanciaM += getValor(vacioFil,vacioCol -1);
                swapValores(vacioFil,vacioCol - 1);
                dibujar();
                break;
            case 'w':
                if(pos == ARRIBA or pos == ARRIBADERECHA or pos == ARRIBAIZQUIERDA){
                    std::cout<<"No puedes moverte para Arriba"<<std::endl;
                    break;
                }
                distanciaM += getValor(vacioFil - 1, vacioCol);
                swapValores(vacioFil - 1, vacioCol);
                dibujar();
                break;
            case 'd':
                if(pos == DERECHA or pos == ARRIBADERECHA or pos == ABAJODERECHA){
                    std::cout<<"No puedes moverte para Derecha"<<std::endl;
                    break;
                }
                distanciaM += getValor(vacioFil, vacioCol + 1);
                swapValores(vacioFil, vacioCol + 1);
                dibujar();
                break;
            case 's':
                if(pos == ABAJO or pos == ABAJODERECHA or pos == ABAJOIZQUIERDA){
                    std::cout<<"No puedes moverte para ABAJO"<<std::endl;
                    break;
                }
                distanciaM += getValor(vacioFil + 1, vacioCol);
                swapValores(vacioFil + 1, vacioCol);
                dibujar();
                break;
            case 'm':
                std::cout<<"GUARDADO"<<std::endl;
                memoria = matriz;
                mFil = vacioFil;
                mCol = vacioCol;
                mResuleto = distanciaM;
                break;
            case 'r':
                std::cout<<"REGRESANDO"<<std::endl;
                matriz = memoria;
                vacioFil = mFil;
                vacioCol = mCol;
                distanciaM = mResuleto;
                break;
            default:
                std::cout<<"Escriba uno de los comandos a,w,s o d"<<std::endl;
                break;
        }
    }
    std::cout<<"BUENA, LO RESOLVISTE"<<std::endl;
    print();
}

Puzzle::Puzzle(std::map<int,std::map<int,Square>> matriz,std::string name, int fil,int col, int distanciaM,BITMAP * buffer,BITMAP * imagen){
    this->matriz = matriz;
    this->name = name;
    image = imagen;
    vacioCol = col;
    vacioFil = fil;
    this->distanciaM = distanciaM;
    this->buffer = buffer;
}

void Puzzle::swapValores(int fil, int col){
    Square nuevoVacio = matriz[fil][col];
    Square atras = matriz[vacioFil][vacioCol];
    int tempX = nuevoVacio.X;
    int tempY = nuevoVacio.Y;
    nuevoVacio.X = atras.X;
    nuevoVacio.Y = atras.Y;
    nuevoVacio.fil = vacioFil;
    nuevoVacio.col = vacioCol;
    atras.fil = fil;
    atras.col = col;
    atras.X = tempX;
    atras.Y = tempY;

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

std::tuple<int,int> Puzzle::getVacio(){
    return std::make_tuple(vacioFil,vacioCol);
}

int Puzzle::estaResuelto(){
    return distanciaM;
}

void Puzzle::print(){
    for(int i = 1; i <= matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            std::cout<<matriz[i][j].valor<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

std::list<Puzzle::Square> Puzzle::getVecinos(int filS, int colS, int filAnterior, int colAnterior){
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
    while(!juego.desplegar(camino,distanciaM)){
        camino.clear();
    }
    camino.push_front(Puzzle (matriz,name,vacioFil,vacioCol,distanciaM,buffer,image));
    actual = camino.begin();
    nextPorPaso(camino);
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
    for(int i = 0 ; i < 100000000; i++){};
    vacioFil = (*actual).vacioFil;
    vacioCol = (*actual).vacioCol;
    dibujar();
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
    void (*des)(Puzzle, std::list<std::tuple<int,Puzzle>>&, Puzzle, int,int);
    des = desple;
    juego = ArbolDeJuego<Puzzle>(-1,1,des,n*n);
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
    distanciaM = 0;


    int altoImagen  = image->h;
    int anchoImagen = image->w;
    int posY = (ALTO_VENTANA - (altoImagen + INTERLINEADO * n)) / 2;
    int posX = (ANCHO_VENTANA - (anchoImagen + INTERLINEADO * n)) / 2;
    int tempX = posX;


    for(int i = 0; i < n;i++){
        for(int j = 0; j < n; j++){
            std::string sN  = std::to_string(m[i][j] - 1);
            std::string img = name + "/" + name + "-" + sN+ ".pcx";
            matriz[i+1][j+1] = Square(i+1,j+1,m[i][j],n,img,posX,posY);
            posX += x + INTERLINEADO;
            if(m[i][j] == n*n){
                vacioFil = i+1;
                vacioCol = j+1;
            }
            if(m[i][j] != matriz[i+1][j+1].getValorReal()) distanciaM++;
        }
        posY += y + INTERLINEADO;
        posX = tempX;
    }
    Puzzle nuevo(matriz,name,vacioFil,vacioCol,distanciaM,buffer,image);
    juego.insert(nuevo,distanciaM);
    std::cout<<"hola"<<std::endl;
}

Puzzle::Puzzle(int n, std::string name,BITMAP * buffer, std::string extension){
    void (*des)(Puzzle, std::list<std::tuple<int,Puzzle>>&, Puzzle, int,int);
    des = desple;
    juego = ArbolDeJuego<Puzzle>(-1,1,des,n*n);
    distanciaM = 0;
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
    for(int i = 1; i <= n * n; i++){
        valores.push_back(i);
    }
    for(int i = 1; i <= n; i++){
        if(valores.empty())break;
        for(int j = 1; j <= n; j++){
            int h = rand() % valores.size();
            int numero = valores[h];
            std::string sN = std::to_string(numero - 1);
            std::string img = name + "/" + name + "-" + sN+ ".pcx";
            matriz[i][j] = Square(i,j,numero,n,img,posX,posY);
            posX += x + INTERLINEADO;
            if(numero == n * n){
               vacioFil = i;
               vacioCol = j;
            }
            if(numero != matriz[i][j].getValorReal()) distanciaM++;
            valores.erase(valores.begin() + h);
        }
        posY += y + INTERLINEADO;
        posX = tempX;
    }

    Puzzle nuevo(matriz,name,vacioFil,vacioCol,distanciaM,buffer,image);
    juego.insert(nuevo,distanciaM);
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
}



Puzzle::Square::Square(int fil, int col, int val,int n, std::string img,int X, int Y){
    this->fil = fil;
    this->col = col;
    this->n = n;
    valor = val;
    image = img;
    imagen = load_bitmap(img.c_str(),NULL);
    this->X = X;
    this->Y = Y;
}

Puzzle::~Puzzle(){
   /* for(int i = 1; i <= matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            delete matriz[i][j];
        }
    }
    */
}



void desple(Puzzle actual, std::list<std::tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto, int valorActual){
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
    std::list<Puzzle::Square> vecinos = actual.getVecinos(actual.vacioFil,actual.vacioCol,filAnte,colAnte);
    Puzzle temp = actual;
    //cout<<"DESPLEGANDO"<<endl<<endl;
    //actual.print();

    for(Puzzle::Square s : vecinos){
        //cout<<"VECINO->"<<s.valor<<endl;
        actual = temp;
        //if(actual.getValor(s.fil,s.col) != valorIncorrecto){
            int valor =  valorActual + actual.getValor(s.fil,s.col);
                actual.swapValores(s.fil,s.col);
                //cout<<"DESPLIEGUE"<<endl<<endl;
                //actual.print();
                resultado.push_back(std::make_tuple(valor,actual));
        //}
    }
}


#endif // PUZZLE_H
