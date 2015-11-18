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



    m[0][0] = 6;
    m[0][1] = 9;
    m[0][2] = 7;
    m[1][0] = 2;
    m[1][1] = 1;
    m[1][2] = 8;
    m[2][0] = 5;
    m[2][1] = 3;
    m[2][2] = 4;

    Puzzle puz(m,n,"puz");
    puz.Resolver();
}
