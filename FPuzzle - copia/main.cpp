#include <iostream>
#include "time.h"
#include "stdlib.h"
#include "Puzzle.h"

using namespace std;

int main()
{
    srand(time(NULL));
    int n = 4;
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

    Puzzle puz(m,n,"puz");
    puz.Resolver();
}
