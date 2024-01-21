// Copyright 2024 Nash Sun.

#include "scd.hpp"

int main(int argc, char **argv) {
    switch (argc) {
    case 1:
    read_lines("history");
    display_history();
    leap_ui("history");
    break;

    case 2:
    if((std::string)argv[1] == "f") {
        read_lines("frequency");
        display_frequency();
        leap_ui("frequency");
    }
    if((std::string)argv[1] == "m") {
        read_lines("marks");
        display_marks();
        leap_ui("marks");
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