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
    int **m2;
    //int **m4;
    int ** m5;

    m = new int *[n];
    m2 = new int *[n];
    m5 = new int *[n];
    //m4 = new int *[n];
    for(int i = 0; i < n; i++){
        m[i] = new int[n];
        m2[i] = new int[n];
        m5[i] = new int[n];
      //  m4[i] = new int[n];
    }
    /*
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin>>m[i][j];
        }
    }
*/

        ///NO SOLUCIONADO(Search, +nivel,sin marcado)
        ///NO SOLUCIONADO(Search, nivel 0,sin marcado)
        ///HACE BUCLE(Ciclo, nivel 0, sin marcado)
        ///HACE BUCLE(Ciclo, +nivel, sin marcado)
        ///NO SOLUCIONADO(Search, +nivel, con marcado)
        ///NO SOLUCIONADO(Search, nivel 0, con marcado)
    /*
    m[0][0] = 1;
    m[0][1] = 8;
    m[0][2] = 7;
    m[1][0] = 2;
    m[1][1] = 4;
    m[1][2] = 5;
    m[2][0] = 6;
    m[2][1] = 3;
    m[2][2] = 9;
    */

        ///SOLUCIONADO 11(Search, +nivel,sin marcado)
        ///SOLUCIONADO 11(Search, nivel 0,sin marcado)
        ///SOLUCIONADO 11(Ciclo, nivel 0, sin marcado)
        ///SOLUCIONADO 11(Ciclo, +nivel, sin marcado)
        ///SOLUCIONADO 11(Search, +nivel, con marcado)
        ///SOLUCIONADO 11(Search, nivel 0, con marcado)
    /*
    m[0][0] = 4;
    m[0][1] = 1;
    m[0][2] = 9;
    m[1][0] = 5;
    m[1][1] = 8;
    m[1][2] = 2;
    m[2][0] = 7;
    m[2][1] = 6;
    m[2][2] = 3;
    */

            ///SOLUCIONADO 22(Search, +nivel,sin marcado)
            ///NO SOLUCIONADO(Search, nivel 0, sin marcado)
            ///HACE BUCLE(Ciclo, nivel 0, sin marcado)
            ///SOLUCIONADO 22(Ciclo, +nivel, sin marcado)
            ///NO SOLUCIONADO(Search, +nivel, con marcado)
            ///SOLUCIONADO 60(Search, nivel 0, con marcado)

    m2[0][0] = 6;
    m2[0][1] = 9;
    m2[0][2] = 7;
    m2[1][0] = 2;
    m2[1][1] = 1;
    m2[1][2] = 8;
    m2[2][0] = 5;
    m2[2][1] = 3;
    m2[2][2] = 4;


        ///NO SOLUCIONADO(Search, +nivel,sin marcado)
        ///SOLUCIONADO 36(Search, nivel 0, sin marcado)
        ///SOLUCIONADO 36(Ciclo, nivel 0, sin marcado)
        ///HACE BUCLE(Ciclo, +nivel, sin marcado)
        ///NO SOLUCIONADO(Search, +nivel, con marcado)
        ///SOLUCIONADO 40(Search, nivel 0, con marcado)
    /*
    m2[0][0] = 3;
    m2[0][1] = 7;
    m2[0][2] = 8;
    m2[1][0] = 4;
    m2[1][1] = 1;
    m2[1][2] = 5;
    m2[2][0] = 6;
    m2[2][1] = 9;
    m2[2][2] = 2;
    */

/*
    m4[0][0] = 6;
    m4[0][1] = 1;
    m4[0][2] = 4;
    m4[0][3] = 10;
    m4[1][0] = 7;
    m4[1][1] = 5;
    m4[1][2] = 12;
    m4[1][3] = 3;
    m4[2][0] = 2;
    m4[2][1] = 8;
    m4[2][2] = 15;
    m4[2][3] = 11;
    m4[3][0] = 9;
    m4[3][1] = 14;
    m4[3][2] = 13;
    m4[3][3] = 16;
*/
    /*
    m5[0][0] = 2;
    m5[0][1] = 6;
    m5[0][2] = 24;
    m5[0][3] = 20;
    m5[0][4] = 14;
    m5[1][0] = 1;
    m5[1][1] = 12;
    m5[1][2] = 8;
    m5[1][3] = 4;
    m5[1][4] = 10;
    m5[2][0] = 3;
    m5[2][1] = 17;
    m5[2][2] = 19;
    m5[2][3] = 25;
    m5[2][4] = 18;
    m5[3][0] = 7;
    m5[3][1] = 22;
    m5[3][2] = 16;
    m5[3][3] = 9;
    m5[3][4] = 13;
    m5[4][0] = 21;
    m5[4][1] = 11;
    m5[4][2] = 15;
    m5[4][3] = 5;
    m5[4][4] = 23;
*/
    allegro_init();
    install_keyboard();

    set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO_VENTANA, ALTO_VENTANA, 0, 0);

    BITMAP *buffer = create_bitmap(ANCHO_VENTANA,ALTO_VENTANA);
    clear_to_color(buffer, 0x999999);

    Puzzle puz(m2,n,"R",buffer,".bmp");
    //Puzzle puz2(m2,n,"ROMPEYO",buffer,".jpg");
    puz.dibujar();
    puz.Resolver();

    destroy_bitmap(buffer);
    puz.destruir();
    return 0;
}
