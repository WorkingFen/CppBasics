/**
* Name: main.cpp
* Purpose: main
*
* @version 1.24 06/01/2018
*/

#include "Instructions.h"

int main(int argc, char** argv)
{
    unsigned vertices;
    std::vector<std::vector<unsigned>> array;
    std::vector<std::pair<unsigned, unsigned>> array_out;
    Instructions instructions;

    instructions.load_file(argv[1]);
    instructions.load(array, vertices);
    instructions.algorithm(array, array_out, vertices);
    instructions.save(array_out, vertices);
}

