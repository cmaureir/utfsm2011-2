#include "scattersearch.hpp"

// Generar Soluciones:
//  Aplica un método de generación con diversidad del conjunto
//  de soluciones en "P" de tamaño «popsize».
void solutions_generation()
{
    cout << "solutions_generation()" << endl;
    // Fixed seed
    srand(123456789);

    int i, j, r;
    int ids[bs.size()];
    int tmp;

    // Sorted sequence of the boxes
    for (i = 0; i < (int)bs.size(); i++) ids[i] = i+1;

    // Shuffle of the boxes order
    for (i = 0; i < popsize; i++) {
        solution tmp_sol;
        for (j = 0; j < (int)bs.size(); j++) {
            r = j + (rand() % (bs.size()-j));
            tmp = ids[j];
            ids[j] = ids[r];
            ids[r] = tmp;
        }

        // Adding suffled boxes to the solutions struct
        for (j = 0; j < (int)bs.size(); j++) {
            tmp_sol.items.push_back(ids[j]);
        }

        // Temp fitness
        tmp_sol.fitness = -1.0;
        tmp_sol.height  = 0;
        sols.push_back(tmp_sol);
    }
}

// Mejorar Soluciones:
//  Aplica un método de búsqueda local para mejorar las
//  soluciones generadas en el paso previo.
void solutions_improvment()
{
    cout << "solutions_improvment()" << endl;
    // TO DO
    // Grasp
}

// Construir el conjunto de referencia RefSet:
//  Elegir las mejores «b» soluciones para construir el conjunto RefSet.
//  El conjunto RefSet es un conjunto de «b» soluciones que se usarán para
//  generar nuevas soluciones al combinarlas por algún método.
void refset_build()
{
    cout << "refset_build()" << endl;
    // TO DO
    // Ordenar soluciones de la poblacion por el fitness
    // Seleccionar los «b» mejores y hacer push en RefSet.
}

// Inicializar:
//  Identificar la mejor solución en RefSet como la mejor actual.
void initialize()
{
    cout << "initialize()" << endl;
    // TO DO
    // check
    best = refset.at(refset.size());
}

// Combinar Soluciones:
//  Generar intentos de soluciones usando todos los pares de soluciones de RefSet,
//  tal que al menos una solucion de cada una sea nueva.
void solutions_combination()
{
    cout << "solutions_combination()" << endl;
    // TO DO
    // Movimiento de "mutación"
    // Arreglar método de fitness pare que reciba parametro.
    // Generamos 2 o 3 nuevas soluciones de cada una dentro de refset
}

// Modificar el conjunto de referencia (refset)
//  Elegir las mejores «b» soluciones de la unión entre RefSet con el conjunto
//  «b(b-1)/2» de soluciones generadas en el paso anterior.
void refset_modification()
{
    cout << "refset_modification()" << endl;
    // TO DO
    // crear un nuevo vector con la union
    // refset nuevo con la seleccion de la union
}

// Modificar el mejor:
//  Identificar la mejor solución de RefSet
void best_modification()
{
    cout << "best_modification()" << endl;
    // TO DO
    // generamos X modificaciones del mejor y las guardamos en refset.
}

// Reconstruir RefSet:
//  Eliminar las «b/2» soluciones en RefSet.
//  Generar «popsize» soluciones mejoradas aplicando "solutions_generation" y
//  "solutions_improvment".
//  Elegir «b/2» soluciones "diversas" y agregarlas a RefSet.
void refset_rebuild()
{
    cout << "refset_rebuild()" << endl;
    // TO DO
    // eliminamos las b/2 peores.
    // generamos popsize mejores random + grasp
    // elegimos las b/2 soluciones mas "malas".
}


// BL approach
void fitness_calculation(){

    int i, j, k;
    int n = (int)bs.size();
    int a, b, w, h, a_p, b_p, w_p, h_p, a_tmp, b_tmp;
    int top, new_top;
    bool valid;

    for (i = 0; i < popsize; i++)
        {
        top = 0;
        // Solution «items»  item = sols.at(i).items.at(j)
        for (j = 0; j < n; j++)
        {
            a = 0; b = 0;
            a_tmp = 0; b_tmp = 0;

            valid = false;
            cout << "+ Elemento: " << sols.at(i).items.at(j) << endl;

            w = bs.at(sols.at(i).items.at(j)-1).width;
            h = bs.at(sols.at(i).items.at(j)-1).height;

            for (k = 0; k < j; k++)
            {
                // Doble for, con los a_i y despues b_i
                // 0 <= a_i <= w - w_i
                // 0 <= b_i

                cout << "\tCon " << sols.at(i).items.at(j) << " (w,h) = (" << w << "," << h << ")" << " reviso " << sols.at(i).items.at(k)  << endl;

                b = b_tmp;
                valid = false;
                while (0 <= b && valid == false)
                {
                    w_p = bs.at(sols.at(i).items.at(k)-1).width;
                    h_p = bs.at(sols.at(i).items.at(k)-1).height;

                    for (a = a_tmp; a <= strip_width - w; a++)
                    {
                        cout << "\t\tPara " << sols.at(i).items.at(k) << " probamos (a,b) = (" << a << "," << b << ")" << endl;
                        a_p = sols.at(i).a.at(k);
                        b_p = sols.at(i).b.at(k);
                        cout << "(" << a << "+" << w << "<=" <<  strip_width << ") && ((";
                        cout << a_p <<"+"<< w_p <<"<=" << a<<") || ( " << a << "+" << w << "<=" << a_p << ") || ";
                        cout << "(" << b_p <<"+"<< h_p <<"<=" <<b<<") || (" << b << "+" << h << "<=" << b_p << "))" << endl;
                        if (
                            (a + w <= strip_width) &&
                            (
                                (a_p + w_p <= a) || (a + w <= a_p) ||
                                (b_p + h_p <= b) || (b + h <= b_p)
                            )
                           )
                        {
                            cout << "valido!" << endl;
                            valid = true;
                            a_tmp = a;
                            b_tmp = b;
                            // TO DO
                            // No respeta espacios en blanco.
                            break;
                        }

                    }
                    if (!valid){
                        b++;
                    }
                getchar();
                }
            }
            // End revisión

            cout << "\t\t\t\tAgregando par de (a,b): (" << a << "," << b << ")" << endl;
            sols.at(i).a.push_back(a);
            sols.at(i).b.push_back(b);
        }

        for (j = 0; j < n; j++)
        {
            new_top = sols.at(i).b.at(j) + bs.at(sols.at(i).items.at(j)-1).height;

            if (new_top > top)
            {
                top  = new_top;
            }
        }

        sols.at(i).height = top;
    }
}


// Print the solutions vector
void print_solutions(){
    cout << "print_solutions()" << endl;
    for (int i = 0; i < popsize; i++) {
        cout << i << "\t:\t";
        for (int j = 0; j < (int)bs.size(); j++) {
            cout << sols.at(i).items.at(j) << " ";
        }
        // cout << " | " << sols.at(i).fitness << endl;
        cout << " | " << sols.at(i).height << endl;
    }
}
