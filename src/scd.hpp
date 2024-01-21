// Copyright 2024 Nash Sun.

#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

#include <string>
#include <deque>
#include <queue>
#include <map>

#include <cstdlib>
#include <cstring>
#include <unistd.h> 


void display_history();
void display_frequency();
void display_marks();

void leap_ui(std::string mode);
void leap(std::string path);

void update_history();
void update_frequency();

void read_lines(std::string mode);

std::string remove_last_file(char *path);