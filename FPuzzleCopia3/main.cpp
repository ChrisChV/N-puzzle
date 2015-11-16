#include <iostream>
#include "time.h"
#include "stdlib.h"
#include "Puzzle.h"

using namespace std;

int main()
{
    srand(time(NULL));
    int n = 3;
    /*
    int ** m;
    m = new int *[n];
    for(int i = 0; i < n; i++){
        m[i] = new int[n];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin>>m[i][j];
        }
    }

    m[0][0] = 9;
    m[0][1] = 8;
    m[0][2] = 6;
    m[1][0] = 2;
    m[1][1] = 7;
    m[1][2] = 4;
    m[2][0] = 5;
    m[2][1] = 3;
    m[2][2] = 1;
    */
    Puzzle puz(n,"puz");
    puz.Resolver();
}
