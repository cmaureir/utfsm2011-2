#ifndef common_hpp
#define common_hpp
#include "common.hpp"
#endif

void solutions_generation();
void solutions_improvment();
void refset_build();
void initialize();
void solutions_combination();
void refset_modification();
void best_modification();
void refset_rebuild();

void fitness_calculation(vector<solution> &tmp);
void print_solutions(vector<solution> tmp);
bool struct_cmp(solution i, solution j);
void sort_solutions(vector<solution> &tmp);
