// Copyright 2024 Nash Sun.

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <utility>

#include <string>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>

#include <cstdlib>
#include <cstring>
#include <unistd.h> 


void display_history();
void display_frequency();
void display_marks();

void leap_ui(std::string mode);
void leap(std::string path);

void update_history(std::string path);
void update_frequency(std::string path);

void read_lines(std::string mode);

std::string remove_last_file(const  char *path);