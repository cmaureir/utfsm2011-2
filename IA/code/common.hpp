#include  <iostream>
#include  <fstream>
#include  <vector>
#include  <ctime>
#include  <cstdlib>
#include  <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

struct box{
    int id;
    int height;
    int width;
};

vector<box> bs;
int strip_width;
int strip_height;

int **strip;
int popsize = 20;

struct solution {
    // items chain
    vector<int> items;

    // Bottom Left corner coordinates per item
    vector<int> a;
    vector<int> b;

    // used percentage
    float p;

    // max height
    int height;

    // fitness of the solution
    float fitness;
};

vector<solution> sols;
vector<solution> refset;
solution best;

// Number of solutions in RefSet
int b = 0.25*popsize;

// Evaluation function evaluations
int eval_num = 0;
int max_eval = 1;
int new_refset_solutions = 0;
