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

    solutions_generation();
    fitness_calculation(sols);

    solutions_improvment(sols);
    refset_build();

    initialize();

    do {
        // número de nuevas soluciones en RefSet
        while (iteration < max_iter){
            cout << iteration << "/" << max_iter << endl;
            iteration++;
            solutions_combination();
            fitness_calculation(new_set);
            solutions_improvment(new_set);
            //refset_modification();
        }
        best_modification();
        refset_rebuild();
        iteration++;
    } while (iteration < max_iter);

    return 0;
}
