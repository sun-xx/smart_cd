// Copyright 2024 Nash Sun.

#include "scd.hpp"
#include <string>

//#define DEBUG_history
//#define DEBUG_frequency
//#define DEBUG_marks

using std::cout;
using std::endl;

std::deque<std::string> history;
std::priority_queue<std::pair<int, std::string> > frequency;
std::map<std::string, std::string> marks;


std::string remove_last_file(char *path) {
    char *last_slash = strrchr(path, '\\');
    if (last_slash == NULL) {
        return path;
    }

    *last_slash = '\0';
    return (std::string)path;
}

void read_lines(std::string mode) {
    std::string path = remove_last_file(_pgmptr);
    std::ifstream fin;
    fin.open(path + "\\" + mode + ".txt", std::ios::in);
    if(!fin) {
        perror( "Cannot open file");
        exit(EXIT_FAILURE);
    }

    if(mode == "history") {
        char line[1024];
        while(!fin.eof()) {
            fin.getline(line, 1024);
            history.push_back((std::string)line);
        }
    }
    if(mode == "frequency") {
        char line[1024];
        int first; std::string second;
        while(!fin.eof()) {
            fin.getline(line, 1024);
            std::stringstream ss((std::string)line);
            ss >> first; ss >> second;
            auto data = std::make_pair(first, second);
            frequency.push(data);
        }
    }
    if(mode == "marks") {
        char line[1024];
        std::string first, second;
        while(!fin.eof()) {
            fin.getline(line, 1024);
            std::stringstream ss((std::string)line);
            ss >> first; ss >> second;
            auto data = std::make_pair(first, second);
            marks.insert(data);
        }
    }

    fin.close();

    #ifdef DEBUG_history
    for(auto i:history) cout<<i<<endl;
    #endif

    #ifdef DEBUG_frequency
    while(!frequency.empty()) {
        cout << frequency.top().first << " " << frequency.top().second << endl;
        frequency.pop();
    }
    #endif

    #ifdef DEBUG_marks
    for(auto i:marks) cout<<i.first<<" "<<i.second<<endl;
    #endif
}
