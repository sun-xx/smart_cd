// Copyright 2024 Nash Sun.

#include "scd.hpp"

//#define DEBUG_history
//#define DEBUG_frequency
//#define DEBUG_marks

using std::cout;
using std::endl;
using std::cin;

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
            std::string s_line = (std::string)line;
            int where = s_line.find(",") + 1;

            std::string first_s = s_line.substr(0, where);
            std::istringstream is(first_s);
            is >> first;

            second = s_line.substr(where, 1024);
            auto data = std::make_pair(first, second);
            frequency.push(data);
        }
    }
    if(mode == "marks") {
        char line[1024];
        std::string first, second;
        while(!fin.eof()) {
            fin.getline(line, 1024);
            std::string s_line = (std::string)line;
            int where = s_line.find(",");

            first = s_line.substr(0, where);
            second = s_line.substr(where + 1, 1024);

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


void display_history() {
    int cnt = 0;
    for(auto i=history.end()-1; i>=history.begin(); --i) {
        cnt++;
        cout << "[" << cnt << "] " << *i << endl;
    }
}


void display_frequency() {
    auto display_fq = frequency;
    int cnt = 0;
    while(!display_fq.empty()) {
        cnt++;
        cout << "[" << cnt << "] " << display_fq.top().second << endl;
        display_fq.pop();
    }
}

void display_marks() {
    for(auto i : marks)
        cout<<"[" << i.first <<"] "<<i.second<<endl;
}

void leap_ui(std::string mode) {
    int choice;
    std::string mark;
    cout << "Input (0 to quit): ";

    if(mode == "history") {
        cin >> choice;
        if(choice == 0) exit(EXIT_SUCCESS);
        leap(history[history.size()-choice]);
    }
    if(mode == "frequency") {
        cin >> choice;
        if(choice == 0) exit(EXIT_SUCCESS);
        for(int i=0; i<choice-1; ++i)
            frequency.pop();
        leap(frequency.top().second);
    }
    if(mode == "marks") {
        cin >> mark;
        if(mark == "0") exit(EXIT_SUCCESS);
        leap(marks.find(mark)->second);
    }
}

void leap(std::string path) {
    system((R"(powershell -NoExit -NoLogo -Command "cd ')" +
    path + R"('")").c_str());
}