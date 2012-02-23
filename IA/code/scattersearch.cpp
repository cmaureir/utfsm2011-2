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

bool is_in_item(int p_a, int p_b, int p_w, int p_h, int w, int h, int a, int b){
    cout << "is_in_item()" << endl;

    for (int k = a; k < a+w ; k++) {
        for (int l = b; l < b+h; l++) {

            for (int j = p_b; j < p_b + p_h ; j++) {
                for (int i = p_a; i < p_a + p_w ; i++) {

                    cout << "Esta  ("<<k<<","<<l<< ") en (" << i << "," << j << ") ?"<< endl;
                    if ( (k == i && l == j) && k != p_a + p_w && l != p_b + p_h)
                        return true;
                }
            }
        }
    }
    return false;

//    if ( ((p_a <= a && a < p_a + p_w) &&
//          (p_b <= b && b < p_a + p_h))
//          ||
//         ((p_a <= a + w && a + w < p_a + p_w) &&
//          (p_b <= b + h && b + h < p_a + p_h))
//          ||
//         ((p_a <= a + w && a + w < p_a + p_w) &&
//          (p_b <= b  && b < p_a + p_h))
//          ||
//         ((p_a <= a && a < p_a + p_w) &&
//          (p_b <= b + h && b + h < p_a + p_h))
//)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
}


// BL approach
void fitness_calculation(vector<solution> &ss){

    int i, j, k;
    int n = (int)bs.size();
    int a, b, w, h, a_p, b_p, w_p, h_p, a_tmp, b_tmp;
    int top, new_top, validos;
    bool valid;

    for (i = 0; i < popsize; i++)
        {
        top = 0;
        // Solution «items»  item = ss.at(i).items.at(j)
        for (j = 0; j < n; j++)
        {
            a = 0; b = 0;
            a_tmp = 0; b_tmp = 0;

            valid = false;
            cout << "+ Elemento: " << ss.at(i).items.at(j) << endl;

            w = bs.at(ss.at(i).items.at(j)-1).width;
            h = bs.at(ss.at(i).items.at(j)-1).height;

            for (k = 0; k < j; k++)
            {
                // Doble for, con los a_i y despues b_i
                // 0 <= a_i <= w - w_i
                // 0 <= b_i

                cout << "\tCon " << ss.at(i).items.at(j) << " reviso " << ss.at(i).items.at(k)  << endl;

                b = b_tmp;
                valid = false;
                while (0 <= b && valid == false)
                {
                    w_p = bs.at(ss.at(i).items.at(k)-1).width;
                    h_p = bs.at(ss.at(i).items.at(k)-1).height;
                    a_tmp = 0;
                    for (a = a_tmp; a < strip_width; a++)
                    {
                        cout << "\t\tPara " << ss.at(i).items.at(k) << " probamos (a,b) = (" << a << "," << b << ")" << endl;
                        a_p = ss.at(i).a.at(k);
                        b_p = ss.at(i).b.at(k);
                        if (
                            (a + w <= strip_width) &&
                            (
                                ((a_p + w_p <= a) || (a + w <= a_p)) ||
                                ((b_p + h_p <= b) || (b + h <= b_p))
                            )
                           )
                        {
                            cout << "Pasa primera condicion..." << endl;

                            validos = 0;
                            for (int ii = 0; ii < j; ii++) {
                                cout << "Somos: " << ss.at(i).items.at(j) << endl;
                                int w_i = bs.at(ss.at(i).items.at(ii)-1).width;
                                int h_i = bs.at(ss.at(i).items.at(ii)-1).height;
                                int a_i = ss.at(i).a.at(ii);
                                int b_i = ss.at(i).b.at(ii);
                                cout << "Revisamos de nuevo : " << ss.at(i).items.at(ii) << endl;
                                cout << " a: " << a_i;
                                cout << " b: " << b_i;
                                cout << " w: " << w_i;
                                cout << " h: " << h_i;
                                cout << endl;
                                if(!is_in_item(a_i, b_i, w_i, h_i, w, h, a, b)) {
                                    cout << "valido!" << endl;
                                    valid = true;
                                    a_tmp = a;
                                    b_tmp = b;
                                    validos++;

                                }
                                else{
                                    cout << "No valido" << endl;
                                }
                                cout << "\t\tvalidos " << validos << "/" << j << endl;
                            }
                            if(valid && validos == j){
                                break;
                            }
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
            ss.at(i).a.push_back(a);
            ss.at(i).b.push_back(b);
        }

        for (j = 0; j < n; j++)
        {
            new_top = ss.at(i).b.at(j) + bs.at(ss.at(i).items.at(j)-1).height;

            if (new_top > top)
            {
                top  = new_top;
            }
        }

        ss.at(i).height = top;
    }
}



//void fitness_calculation(vector<solution> &tmp){
//
//    int w, h, n, a, b;
//    int p_w, p_h, p_a, p_b;
//    solution s;
//    int it, p_it;
//    bool stop;
//
//    for (int i = 0; i < (int)tmp.size(); i++) {
//        s = tmp.at(i); // actual solution
//        n = bs.size(); // total amount of items
//        for (int j = 0; j < n; j++) {
//            it = s.items.at(j);   // actual item
//            w = bs.at(it-1).width;  // actual item width
//            h = bs.at(it-1).height; // actual item height
//            a = 0; b = 0; // starting BL-edge-coordinate
//
//            cout << "* Elemento: " << it << " (w,h) = " << "("<<w<<","<<h<< ")" <<endl;
//
//            // Adding first element
//            if (j == 0){
//                s.a.push_back(a);
//                s.b.push_back(b);
//            }
//            else {
//
//                // Looking for the lowest point
//                stop = 0;
//                while (b >= 0 && stop <= j){
//                    for (a = strip_width; a >= 0; a--) {
//                        cout << "    Probando (a,b) = (" << a << "," << b << ")"<< endl;
//                        // Iteration over the item in the strip
//                        for (int k = 0; k < j; k++) {
//                            p_it = s.items.at(k);       // previous item
//                            p_w = bs.at(p_it-1).width;  // previous item width
//                            p_h = bs.at(p_it-1).height; // previous item height
//                            p_a = s.a.at(k);            // previous item x coordinate
//                            p_b = s.b.at(k);            // previous item y coordinate
//                            cout << "     Entramos p_it = " << p_it << endl;
//
//                            // lowest point search
//                            if(!is_in_item(p_a, p_b, p_w, p_h, w, h, a, b)){
//                                cout << "          Encuentro (a,b) = (" << a << "," << b << ")" << endl;
//                                // leftmost point
//                                int l = a;
//                                while (!is_in_item(p_a, p_b, p_w, p_h, w, h, l, b) ){
//                                    cout << "Buscando izquierda..." << "(a,b) = (" << l << "," << b << ")" << endl;
//
//                                    if ( l == 0 ){
//                                        break;
//                                    }
//                                    l--;
//                                }
//                                a = l + 1;
//                                cout << "             !! Encontrado: ("  << a  << "," << b << ")" << endl;
//                                stop++;
//                                // Verify if fit
//                                // TO DO
//
//                            }
//                            cout << "validos " << stop << "/" << j << endl;
//                            cout << "vamos " << k+1 << "/" << j << endl;
//                            getchar();
//                        }
//                        if (stop == j){
//                            break;
//                        }
//                    }
//                    if (stop == j){
//                        break;
//                    }
//                    cout << "b++" << endl;
//                    b++;
//                }
//                // Saving coordinates
//                cout << "\t\t\t Ingresando (" << a  << "," << b << ")" << endl;
//                s.a.push_back(a);
//                s.b.push_back(b);
//            }
//        }
//    }
//}


// Print the solutions vector
void print_solutions(vector<solution> tmp){
    cout << "print_solutions()" << endl;
    for (int i = 0; i < (int)tmp.size(); i++) {
        cout << i << "\t:\t";
        for (int j = 0; j < (int)tmp.at(i).items.size(); j++) {
            cout << tmp.at(i).items.at(j) << " ";
        }
        // cout << " | " << sols.at(i).fitness << endl;
        cout << " | " << tmp.at(i).height << " | " << tmp.at(i).fitness << endl;
    }
}

bool struct_cmp(solution i, solution j){
    return (i.fitness < j.fitness);
}

void sort_solutions(vector<solution> &tmp){
    sort(tmp.begin(), tmp.end(), struct_cmp);
}
