#pragma once
#ifndef utils_hpp
#define utils_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

struct box {
    int id;
    int height;
    int width;
};

vector<box> bs;
int strip_width;

void read_input_file();
void print_input_file();
bool check_flags(int argc, char *argv[], string &path);

#endif
