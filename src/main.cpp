// Copyright 2024 Nash Sun.

#include "scd.hpp"

const char *e_path;
extern std::string exe_path;
extern std::string remove_last_file(const char *path);

int main(int argc, char **argv) {
    e_path = argv[0];
    exe_path = remove_last_file(e_path);

    switch (argc) {
    case 1:
    read_lines("history");
    read_lines("frequency");
    display_history();
    leap_ui("history");
    break;

    case 2:
    if((std::string)argv[1] == "f") {
        read_lines("history");
        read_lines("frequency");
        display_frequency();
        leap_ui("frequency");
    }
    else if((std::string)argv[1] == "m") {
        read_lines("marks");
        display_marks();
        leap_ui("marks");
    }
    else {
        read_lines("history");
        read_lines("frequency");
        leap((std::string)argv[1]);
    }
    break;

    case 3:
    if((std::string)argv[1] == "m") {
        read_lines("marks");
        extern std::map<std::string, std::string> marks;
        leap(marks.find((std::string)argv[2])->second);
    }
    break;

    }
    
    return 0;
}