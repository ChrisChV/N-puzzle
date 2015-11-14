#include <iostream>
#include "time.h"
#include "stdlib.h"
#include "Puzzle.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Puzzle puz(3,"puz");

    puz.Resolver();
}
