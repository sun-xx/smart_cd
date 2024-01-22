// Copyright 2024 Nash Sun.

#include "scd.hpp"

//#define DEBUG_history
//#define DEBUG_frequency
//#define DEBUG_marks
extern const char *e_path;

using std::cout;
using std::endl;
using std::cin;

std::deque<std::string> history;
std::priority_queue<std::pair<int, std::string> > frequency;
std::map<std::string, std::string> marks;

std::string to_path;
std::string exe_path;

std::string remove_last_file(const char *path) {
    char *last_slash = strrchr(path, '\\');
    if (last_slash == NULL) {
        return path;
    }

    *last_slash = '\0';
    return (std::string)path;
}

void read_lines(std::string mode) {
    std::ifstream fin;
    fin.open(exe_path + "\\" + mode + ".txt", std::ios::in);
    if(!fin) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }
    fin.clear();
    fin.seekg(0, std::ios::beg);

    if(mode == "history") {
        char line[1024];
        history.clear();
        while(!fin.eof()) {
            fin.getline(line, 1024);
            if(!((std::string)line == ""))
                history.push_back((std::string)line);
        }
    }
    if(mode == "frequency") {
        char line[1024];
        int first; std::string second;
        while(!frequency.empty())
            frequency.pop();
        while(!fin.eof()) {
            fin.getline(line, 1024);
            if(!((std::string)line == "")) {
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
    }
    if(mode == "marks") {
        char line[1024];
        std::string first, second;
        marks.clear();
        while(!fin.eof()) {
            fin.getline(line, 1024);
            if(!((std::string)line == "")) {
                std::string s_line = (std::string)line;
                int where = s_line.find(",");

                first = s_line.substr(0, where);
                second = s_line.substr(where + 1, 1024);

                auto data = std::make_pair(first, second);
                marks.insert(data);
            }
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
    std::priority_queue<std::pair<int, std::string> > display_fq;
    display_fq = frequency;
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
        to_path = history[history.size()-choice];
        leap(to_path);
    }
    if(mode == "frequency") {
        cin >> choice;
        if(choice == 0) exit(EXIT_SUCCESS);
        std::priority_queue<std::pair<int, std::string> > temp;
        temp = frequency;
        for(int i=0; i<choice-1; ++i)
            temp.pop();
        to_path = temp.top().second;
        leap(to_path);
    }
    if(mode == "marks") {
        cin >> mark;
        if(mark == "0") exit(EXIT_SUCCESS);
        to_path = marks.find(mark)->second;
        leap(to_path);
    }
}

void leap(std::string path) {
    if(!std::filesystem::exists(path)) {
        cout << "path doesn't exist." << endl;
        exit(EXIT_FAILURE);
    }
    update_frequency(path);
    update_history(path);
    system((R"(powershell -NoExit -NoLogo -Command "cd ')" +
    path + R"('")").c_str());
}


void update_history(std::string path) {
    if(std::count(history.begin(), history.end(), path))
        history.erase(std::find(history.begin(), history.end(), path));
    history.push_back(path);
    while(history.size() > 10)
        history.pop_front();

    std::ofstream fp;
    fp.open(exe_path + "\\" + "history.txt", std::ios::trunc);
    if(!fp) {
        perror( "Cannot open file");
        exit(EXIT_FAILURE);
    }

    for(auto h : history) {
        fp << h << endl;
    }
    fp.close();
}

void update_frequency(std::string path) {
    // This is the last time we use "frequency",
    // so now we don't need to copy it once again.
    std::vector<std::pair<int, std::string> > temp;
    while(!frequency.empty()) {
        temp.push_back(frequency.top());
        frequency.pop();
    }
    std::sort(temp.begin(), temp.end(),
        [](const std::pair<int, std::string> &a, 
           const std::pair<int, std::string> &b){
            return a.first > b.first;
           });
    while(temp.size() > 10)
        temp.pop_back();

    bool flag = false;
    for(int i=0; i<temp.size(); i++) {
        if(temp[i].second == path){
            flag = true;
            temp[i].first = temp[i].first + 1;
        }
    }
    if(flag == false)
        temp.push_back(std::make_pair(1, path));

    std::ofstream fp;
    fp.open(exe_path + "\\" + "frequency.txt", std::ios::trunc);
    if(!fp) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    for(auto f : temp) {
        fp << f.first << "," << f.second << endl;
    }

    fp.close();
}