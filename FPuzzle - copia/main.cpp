#include <iostream>
#include "time.h"
#include "stdlib.h"
#include "Puzzle.h"




using namespace std;

int main()
{
    srand(time(NULL));

    int n = 3;

    int ** m;
    m = new int *[n];
    for(int i = 0; i < n; i++){
        m[i] = new int[n];
    }
    /*
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin>>m[i][j];
        }
    }
*/
    m[0][0] = 6;
    m[0][1] = 9;
    m[0][2] = 7;
    m[1][0] = 2;
    m[1][1] = 1;
    m[1][2] = 8;
    m[2][0] = 5;
    m[2][1] = 3;
    m[2][2] = 4;

    allegro_init();
    install_keyboard();

    set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO_VENTANA, ALTO_VENTANA, 0, 0);


    BITMAP *buffer = create_bitmap(ANCHO_VENTANA,ALTO_VENTANA);
    clear_to_color(buffer, 0x999999);

    Puzzle puz(m,n,"R",buffer,".bmp");
    puz.dibujar();
    puz.Resolver();



    //readkey();

    destroy_bitmap(buffer);
    puz.destruir();
    return 0;

}
