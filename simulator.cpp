#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "environment.h"
using namespace std;

int main(int argc, char* argv[]){

    //Convert string argument to integer.
    int seed = atoi(argv[1]);

    //Initialize the random generator.
    srand(seed);

    Environment environment;

    //Initialize the environment.
    environment.initialization("A");

    //Run the main loop.
    environment.main_loop();

    return 0;
}
