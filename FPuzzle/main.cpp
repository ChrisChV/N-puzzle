#include <iostream>
#include "time.h"
#include "stdlib.h"
#include "Puzzle.h"

using namespace std;

int main()
{
    srand(time(NULL));
    int ** m;
    m = new int *[3];
    for(int i = 0; i < 3; i++){
        m[i] = new int[3];
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cin>>m[i][j];
        }
    }
    Puzzle puz(m,3,"puz");
    puz.Resolver();
}
