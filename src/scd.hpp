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


void display_history(int limit);
void display_frequency();

void leap_hint();
void leap_mark();
void leap(char *dir);

void update_history(int limit);
void update_frequency();

void read_lines(std::string mode);

std::string remove_last_file(char *path);