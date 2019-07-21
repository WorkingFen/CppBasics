/**
* Name: Instructions.cpp
* Purpose: Implementation of instructions
*
* @version 1.39 06/01/2018
*/

#include "Instructions.h"
#define MX 50

void Instructions::load_file(std::string file)
{
    this->file = file;
}

void Instructions::load(std::vector<std::vector<unsigned>> &array, unsigned &vertices)
{
    unsigned x;
    unsigned y;

    this->stream.open(file);
    if(stream.good()){
        stream >> vertices;
        for(unsigned i=0; i<vertices; i++)
            array.push_back(std::vector<unsigned>());

        while(stream >> x){
            stream >> y;
            array.at(x).push_back(y);
            array.at(y).push_back(x);
        }
    }
    else{
        std::string msg = "An error occurred while loading from file " + file;
        throw msg;
    }
    this->stream.close();
}

void Instructions::dfs_visit(std::vector<std::vector<unsigned>> array, unsigned vertice, std::vector<bool> &visited)
{
    visited.at(vertice) = true;
    for(unsigned i=0; i<array.at(vertice).size(); i++){
        if(array.at(vertice).at(i)!=MX && !visited.at(array.at(vertice).at(i))){
            dfs_visit(array, array.at(vertice).at(i), visited);
        }
    }
    return;
}

bool Instructions::dfs(std::vector<std::vector<unsigned>> array, unsigned vertices, std::vector<std::pair<unsigned, unsigned>> &array_out, std::vector<bool> &visited)
{
    bool end = false;
    unsigned x = 0;
    unsigned first;

    for(unsigned i=0; i<vertices; i++)
        for(unsigned j=0; j<array.at(i).size(); j++)
            if(array.at(i).at(j)!=MX)
                first = i;
    dfs_visit(array, first, visited);
    for(unsigned i=0; i<vertices; i++)
        if(!visited.at(i))
            return true;

    return false;
}

void Instructions::algorithm(std::vector<std::vector<unsigned>> array, std::vector<std::pair<unsigned, unsigned>> &array_out, unsigned vertices)
{
    std::vector<bool> visited;
    bool equal=true;
    bool bridge=false;
    std::vector<std::vector<bool>> checked;
    std::vector<std::vector<unsigned>> foo = array;

    if(vertices<=3)
        return;

    for(unsigned i=1; i<vertices; i++){
        if(array.at(i-1).size()!=array.at(i).size()){
            equal=false;
            break;
        }
    }

    if(equal)
        return;

    for(unsigned i=0; i<vertices; i++){
        checked.push_back(std::vector<bool>());
        for(unsigned j=0; j<vertices; j++)
            checked.at(i).push_back(false);
    }

    for(unsigned i=0; i<vertices; i++){
        for(unsigned j=0; j<array.at(i).size(); j++){
            if(!checked.at(i).at(array.at(i).at(j))){
                for(unsigned k=0; k<foo.at(array.at(i).at(j)).size(); k++){
                    foo.at(array.at(i).at(j)).at(k)=MX;
                }
                for(unsigned k=0; k<foo.at(i).size(); k++){
                    foo.at(i).at(k)=MX;
                }

                visited.clear();
                for(unsigned i=0; i<vertices; i++){
                    visited.push_back(false);
                }
                visited.at(i)= true;
                visited.at(array.at(i).at(j)) = true;

                /*for(unsigned i=0; i<vertices; i++){
                    std::cout << "| ";
                    for(unsigned j=0; j<foo.at(i).size(); j++){
                        std::cout << foo.at(i).at(j) << " ";
                    }
                    std::cout << "|" << std::endl;
                }
                std::cout << std::endl;*/

                bridge = dfs(foo, vertices, array_out, visited);
                if(bridge)
                    array_out.push_back(std::pair<unsigned, unsigned>(i, array.at(i).at(j)));
                bridge = false;
                foo = array;
                checked.at(i).at(array.at(i).at(j)) = true;
                checked.at(array.at(i).at(j)).at(i) = true;
            }
        }
    }

}

void Instructions::save(std::vector<std::pair<unsigned, unsigned>> array_out, unsigned vertices)
{
    this->stream_out.open(this->file+"answer.txt");
    if(stream_out.good()){
        stream_out << "> ./Graphs < " << this->file << std::endl;
        for(unsigned i=0; i<array_out.size(); i++){
            stream_out << array_out.at(i).first << " ";
            stream_out << array_out.at(i).second << std::endl;
        }
        stream_out << ">";
    }
    else{
        std::string msg = "An error occurred while creating file answer.txt";
        throw msg;
    }
    this->stream_out.close();
}
