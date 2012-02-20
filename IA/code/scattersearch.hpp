#pragma once
#ifndef scattersearch_hpp
#define scattersearch_hpp
#include "utils.hpp"

// TO DO:
//
// Solution structure
// Evaluations variables

int popsize = 10;

struct solution {
    // items chain
    vector<int> items;

    // Bottom Left corner coordinates per item
    vector<int> a;
    vector<int> b;

    // max height
    int height;

    // fitness of the solution
    float fitness;
};

vector<solution> sols;
vector<solution> refset;
solution best;

// Number of solutions in RefSet
int b = 0.15*popsize;

// Evaluation function evaluations
int eval_num = 0;
int max_eval = 1;
int new_refset_solutions = 0;

void solutions_generation();
void solutions_improvment();
void refset_build();
void initialize();
void solutions_combination();
void refset_modification();
void best_modification();
void refset_rebuild();

void fitness_calculation();
void print_solutions();
#endif
