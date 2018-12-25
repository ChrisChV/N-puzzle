#include <iostream>
#include <fstream>
#include "time.h"
#include "stdlib.h"
#include "Puzzle.h"

using namespace std;

const string HELP_PATH = "../help";
const string SIN_FILE = "_SIN_FILE_";


void splitFileImg(string img, string & name, string & extention){
    name.clear();
    extention.clear();
    bool flag = false;
    string temp = "";
    string total = "";
    for(char c : img){
        if(c == '/'){
            total += "/" + temp;
            temp.clear();
        }
        else temp.push_back(c);
    }
    for(char c : temp){
        if(c == '.'){
            extention.push_back(c);
            flag = true;
        }
        else if(flag == false) name.push_back(c);
        else extention.push_back(c);
    }
}

int main(int argc, char ** argv){
    if(argc < 2){
        cout<<"Faltan argumentos. Utilize el comando --help"<<endl;
        return 1;
    }
    string option1(argv[1]);
    string option = "";
    string imageFile = "";
    string matrixFile = SIN_FILE;
    string name = "";
    string extention = "";
    bool user = true;
    bool computer = false;
    int n = 3;
    
    if(option1 == "--help"){
        string command = "cat " + HELP_PATH;
        system(command.c_str());
    }
    else{
        imageFile = option1;
        splitFileImg(imageFile, name, extention);
        string cp = "cp " + imageFile + " ./" + name + extention;
        system(cp.c_str());
        for(int i = 2; i < argc; i++){
            option = argv[i];
            if(option == "-f"){
                if(argc < i + 1){
                    cout<<"El argumento -f debe ir seguido de un archivo"<<endl;
                    return 1;
                }
                matrixFile = argv[i + 1];
                i++;
            }
            else if(option == "-u"){
                user = true;
                computer = false;
            }
            else if(option == "-c"){
                user = false;
                computer = true;
            }
            else if(option == "-n"){
                if(argc < i + 1){
                    cout<<"El argumento -f debe ir seguido de un numero"<<endl;
                    return 1;
                }
                option = string(argv[i + 1]);
                i++;
                n = stoi(option);
            }
        }

        srand(time(NULL));

        Puzzle puz;

        allegro_init();
        install_keyboard();

        set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO_VENTANA, ALTO_VENTANA, 0, 0);

        BITMAP *buffer = create_bitmap(ANCHO_VENTANA,ALTO_VENTANA);
        clear_to_color(buffer, 0x999999);

        cout<<name<<endl;
        cout<<extention<<endl;

        if(matrixFile != SIN_FILE){
            int **m2;

            m2 = new int *[n];
        
        
            for(int i = 0; i < n; i++){        
                m2[i] = new int[n];
            }

            ifstream matrix(matrixFile);
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    matrix >> m2[i][j];
                }
            }
            matrix.close();

            puz = Puzzle(m2, n, name, buffer, extention);

        }
        else{
            puz = Puzzle(n, name, buffer, extention);
        }

        puz.dibujar();

        if(user == true){
            puz.ResolverUsuario();
        }
        else{
            puz.Resolver();
        }

        destroy_bitmap(buffer);
        puz.destruir();
        return 0;
    }



   
}
