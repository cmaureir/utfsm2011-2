#include "scattersearch.hpp"

int main(int argc, char *argv[]) {

    // Configuration
    string path;
    if(!check_flags(argc,argv,path)){
        return 1;
    }
    read_input_file(path);

    // Algorithm

    solutions_generation();
    fitness_calculation(sols);

    solutions_improvment();
    refset_build();

    initialize();

    refset_modification();
    cout << "new refset" << endl;
    print_solutions(refset);

    return 0;

    do {
        // nuevas soluciones en RefSet y Núm. función de evaluación < MaxEval
        // Repeticion mientras se sigan agregando nuevas soluciones
        //  al conjunto de referencia.
        while (eval_num < max_eval){
            solutions_combination();
            fitness_calculation(new_set);
            solutions_improvment();
            refset_modification();
        }
        best_modification();
        refset_rebuild();
    // Número de evaluaciones de función de evaluación < MaxEval
    // Se termina cuando se han realizado un todal de MaxEval de evaluaciones
    //   de la función de evaluación.
    } while (iteration < max_iter);
    return 0;
}
