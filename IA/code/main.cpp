#include "scattersearch.hpp"

int main(int argc, char *argv[]) {

    // Configuration
    string path;
    if(!check_flags(argc,argv,path)){
        return 1;
    }
    read_input_file(path);

    // Algorithm
    int iteration = 0;

    solutions_generation(sols);
    fitness_calculation(sols);

    solutions_improvment(sols);
    refset_build();
    //print_solutions(sols);
    cout << endl;
    //print_solutions(refset);

    save_best_solution(refset);

    do {
        // número de nuevas soluciones en RefSet
        while (1)
        {
            refset_tmp = refset;
            solutions_combination();
            fitness_calculation(new_set);
            solutions_improvment(new_set);
            refset_modification();
            cout << get_difference(refset_tmp,refset) << endl;
            getchar();
        }
        save_best_solution(refset);
        refset_rebuild();
        iteration++;
    } while (iteration < max_iter);

    return 0;
}
