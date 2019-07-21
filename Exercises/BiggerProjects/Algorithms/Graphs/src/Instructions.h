/**
* Name: Instructions.h
* Purpose: Declaration of instructions
*
* @version 1.21 06/01/2018
*/
#pragma once

#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>

class Instructions{
    private:
        std::ifstream stream;
        std::ofstream stream_out;
        std::string file;

    public:
        void load_file(std::string file);
        void load(std::vector<std::vector<unsigned>> &array, unsigned &vertices);
        void dfs_visit(std::vector<std::vector<unsigned>> array, unsigned vertice, std::vector<bool> &visited);
        bool dfs(std::vector<std::vector<unsigned>> array, unsigned vertices, std::vector<std::pair<unsigned, unsigned>> &array_out, std::vector<bool> &visited);
        void algorithm(std::vector<std::vector<unsigned>> array, std::vector<std::pair<unsigned, unsigned>> &array_out, unsigned vertices);
        void save(std::vector<std::pair<unsigned, unsigned>> array_out, unsigned vertices);
};
