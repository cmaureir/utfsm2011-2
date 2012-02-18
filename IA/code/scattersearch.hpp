#pragma once
#ifndef scattersearch_hpp
#define scattersearch_hpp
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

// TO DO:
//
// Solution structure
// Evaluations variables

// Evaluation function evaluations
int eval_number = 0;
int max_eval = 1;

void solutions_generation();
void solutions_improvment();
void refset_build();
void initialize();
void solutions_combination();
void refset_modification();
void best_modification();
void refset_rebuild();
#endif
