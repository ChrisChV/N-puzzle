#include <iostream>
#include "time.h"
#include "stdlib.h"
#include "Puzzle.h"


using namespace std;

int main(int argc, char ** argv){
    


    srand(time(NULL));

    int n = 4;

    
    int **m2;

    m2 = new int *[n];
    
    
    for(int i = 0; i < n; i++){        
        m2[i] = new int[n];
    }

    m2[0][0] = 6;
    m2[0][1] = 9;
    m2[0][2] = 7;
    m2[1][0] = 2;
    m2[1][1] = 1;
    m2[1][2] = 8;
    m2[2][0] = 5;
    m2[2][1] = 3;
    m2[2][2] = 4;


    allegro_init();
    install_keyboard();

    set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO_VENTANA, ALTO_VENTANA, 0, 0);

    BITMAP *buffer = create_bitmap(ANCHO_VENTANA,ALTO_VENTANA);
    clear_to_color(buffer, 0x999999);

    Puzzle puz(n,"R",buffer,".bmp");
    //Puzzle puz2(m2,n,"ROMPEYO",buffer,".jpg");
    puz.dibujar();
    puz.ResolverUsuario();

    destroy_bitmap(buffer);
    puz.destruir();
    return 0;
}
