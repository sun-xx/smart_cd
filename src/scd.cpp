// Copyright 2024 Nash Sun.

#include "scd.hpp"
#include <iostream>
#include <string>

#define DEBUG

std::vector<std::string> paths;

char *remove_last_file(char *path) {
    char *last_slash = strrchr(path, '\\');
    if (last_slash == NULL) {
        return path;
    }

    *last_slash = '\0';
    return path;
}

void read_lines(std::string filename) {
    std::string path = (std::string)remove_last_file(_pgmptr);
    std::ifstream fin;
    fin.open(path + "\\" + filename, std::ios::in);
    if(!fin) {
        perror( "Cannot open file");
        exit(EXIT_FAILURE);
    }

    std::string line;
    while(fin >> line) {
        paths.push_back(line);
    }

    fin.close();

    #ifdef DEBUG
    for(auto i:paths) std::cout<<i<<std::endl;
    #endif
}
