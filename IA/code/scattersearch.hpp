#include "common.hpp"

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

void read_input_file(string path);
void print_input_file();
bool check_flags(int argc, char *argv[], string &path);

bool search_fit(int item, int item_w, int item_h, int &a, int &b, int &h, int **strip);
void place_item(int item, int item_w, int item_h, int a, int b, int **strip);
void print_strip(vector<int> tmp, int h, int **strip);
void clear_strip(int **strip);
