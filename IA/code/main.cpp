#include "utils.cpp"
#include "scattersearch.cpp"

int main(int argc, char *argv[]) {

    // Configuration
    string path;
    if(!check_flags(argc,argv,path)){
        return 1;
    }
    read_input_file(path);
    //print_input_file();

    // Algorithm

    solutions_generation();
    print_solutions();
    fitness_calculation();
    print_solutions();
    return 0;
    solutions_improvment();
    refset_build();
    initialize();

    do {
        // nuevas soluciones en RefSet y Núm. función de evaluación < MaxEval
        // Repeticion mientras se sigan agregando nuevas soluciones
        //  al conjunto de referencia.
        while (new_refset_solutions < max_eval && eval_num < max_eval){
            solutions_combination();
            solutions_improvment();
            refset_modification();
        }
        best_modification();
        refset_rebuild();
    // Número de evaluaciones de función de evaluación < MaxEval
    // Se termina cuando se han realizado un todal de MaxEval de evaluaciones
    //   de la función de evaluación.
    } while (eval_num < max_eval);
    return 0;
}
