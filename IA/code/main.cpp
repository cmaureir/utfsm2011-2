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
    int loop;
    int watch_best;
    int best_fitness;

    solutions_generation(sols);
    fitness_calculation(sols);

    solutions_improvement(sols);
    refset_build();
    //print_solutions(sols);
    //cout << endl;
    //print_solutions(refset);

    save_best_solution(refset);
    refset_tmp = refset;

    do {
        // número de nuevas soluciones en RefSet
        loop = 0;
        while (get_difference(refset_tmp,refset) != 0 && iteration && loop < 5)
        {
            refset_tmp = refset;
            solutions_combination();
            fitness_calculation(new_set);
            solutions_improvement(new_set);
            refset_modification(new_set);
            loop++;
        }
        save_best_solution(refset);

        /* A: Si encontramos el óptimo, terminamos */
        if(best.p == 100){
            iteration = max_iter;
        }
        /* A: end */

        /* B: Verificamos cuantas veces el mejor fitness se repite */
        if(best_fitness == best.fitness){
            watch_best++;
        }
        else
        {
            watch_best = 0;
        }

        // Si se ha estancado el 10% de la iteraciones, terminamos
        if (watch_best == max_iter*0.2){
            iteration = max_iter;
        }
        /* B: end */

        refset_rebuild();
        best_fitness = best.fitness;
        iteration++;
    } while (iteration < max_iter);
    print_one_solution(best);

    return 0;
}
