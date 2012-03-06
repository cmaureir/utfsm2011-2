#include "scattersearch.hpp"

vector<solution> sols;
vector<solution> refset;
vector<solution> new_set;
solution best;
vector<box> bs;
int strip_width;
int strip_height;

// Generar Soluciones:
//  Aplica un método de generación con diversidad del conjunto
//  de soluciones en "P" de tamaño «popsize».
void solutions_generation()
{
    cout << "solutions_generation()" << endl;
    // Fixed seed
    srand(123456789);

    int i, j, k, r;
    int ids[bs.size()];
    int tmp;
    int **strip_tmp;

    // Sorted sequence of the boxes
    for (i = 0; i < (int)bs.size(); i++) ids[i] = i+1;

    // filling strip with 0
    strip_tmp = new int*[strip_width];
    for (j = 0; j < strip_width; j++) {
        strip_tmp[j] = new int[strip_height];
        for (k = 0; k < strip_height; k++) {
            strip_tmp[j][k] = 0;
        }
    }

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
        tmp_sol.strip = strip_tmp;

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
    int i;
    vector<solution> tmp;
    // Ordenar soluciones de la poblacion por el fitness
    for (i = 0; i < popsize; i++) {
        tmp.push_back(sols[i]);
    }
    sort_solutions(tmp);
    // Seleccionar los «b» mejores y hacer push en RefSet.
    for (i = 0; i < b; i++) {
        refset.push_back(tmp[i]);
    }
}

// Inicializar:
//  Identificar la mejor solución en RefSet como la mejor actual.
void initialize()
{
    cout << "initialize()" << endl;
    best = refset.at(0);
}

bool is_in(solution tmp, vector<solution> tmp_sols)
{
    bool all = true;
    for (int i = 0; i < (int)tmp_sols.size(); i++) {
        for (int j = 0; j < (int)tmp.items.size(); j++) {
            if(tmp.items[j] != tmp_sols[i].items[j]){
                all = false;
            }
            if(!all){
                break;
            }
        }
    }
}


// Combinar Soluciones:
//  Generar intentos de soluciones usando todos los pares de soluciones de RefSet,
//  tal que al menos una solucion de cada una sea nueva.
void solutions_combination()
{
    cout << "solutions_combination()" << endl;
    int begin, end, step;
    int N = (int)bs.size();
    int j, tmp_value;
    vector<int> numbers(N);
    vector<solution> tmp_sol;
    bool new_sol = false;
    // TO DO
    // new_set las guardará.
    // Movimiento de "mutación"
    // Generamos 2 o 3 nuevas soluciones de cada una dentro de refset
    // Pueden ser cortar y mover partes, o seleccionar n elementos y moverlos al medio o al final.

    for (int i = 0; i < (int)refset.size(); i++) {
        tmp_sol.push_back(refset[i]);
    }

    for (int i = 0; i < (int)refset.size() - 1; i=i+2) {
        new_sol = false;
        while(!new_sol){
            cout << "p1: ";
            for (j = 0; j < N; j++) {
                cout << refset[i].items[j] << " ";
            }
            cout << endl;
            cout << "p2: ";
            for (j = 0; j < N; j++) {
                cout << refset[i+1].items[j] << " ";
            }
            cout << endl;

            begin = (rand() % (N-2));
            end = begin + 2 + (rand() % (N-(begin+2)));
            cout << " * " <<begin << " " << end << endl;

            for (j = begin; j <= end; j++) {
                cout << refset[i].items[j] << " ";
            }
            cout << endl;
            for (j = begin; j <= end; j++) {
                cout << refset[i+1].items[j] << " ";
            }
            cout << endl;

            for (j = begin; j <= end; j++) {
                tmp_value = tmp_sol[i].items[j];
                tmp_sol[i].items[j]   = tmp_sol[i+1].items[j];
                tmp_sol[i+1].items[j] = tmp_value;
            }

            cout << "new p1: ";
            for (j = 0; j < N; j++) {
                cout << tmp_sol[i].items[j] << " ";
            }
            cout << endl;
            cout << "new p2: ";
            for (j = 0; j < N; j++) {
                cout << tmp_sol[i+1].items[j] << " ";
            }
            cout << endl;


            fill(numbers.begin(), numbers.end(),0);
            for (j = 0; j < N; j++) {
                if(numbers[tmp_sol[i].items[j]-1] == 0){
                    numbers[tmp_sol[i].items[j]-1] = 1;
                }
                else{
                    tmp_sol[i].items[j] = 0;
                }
            }
            fill(numbers.begin(), numbers.end(),0);
            for (j = 0; j < N; j++) {
                if(numbers[tmp_sol[i+1].items[j]-1] == 0){
                    numbers[tmp_sol[i+1].items[j]-1] = 1;
                }
                else{
                    tmp_sol[i+1].items[j] = 0;
                }
            }

            cout << "2new p1: ";
            for (j = 0; j < N; j++) {
                cout << tmp_sol[i].items[j] << " ";
            }
            cout << endl;
            cout << "2new p2: ";
            for (j = 0; j < N; j++) {
                cout << tmp_sol[i+1].items[j] << " ";
            }
            cout << endl;


            fill(numbers.begin(), numbers.end(),0);
            for (j = 0; j < N; j++) {
                if(tmp_sol[i].items[j] != 0){
                    numbers[tmp_sol[i].items[j]-1] = 1;
                }
            }
            for (j = 0; j < N; j++) {
                if(numbers[j] == 0){
                    cout << "falta: " << j + 1 << endl;
                    for (int k = 0; k < N; k++) {
                        if(tmp_sol[i].items[k] == 0){
                            tmp_sol[i].items[k] = j + 1;
                            break;
                        }
                    }
                }
            }

            fill(numbers.begin(), numbers.end(),0);
            for (j = 0; j < N; j++) {
                if(tmp_sol[i+1].items[j] != 0){
                    numbers[tmp_sol[i+1].items[j]-1] = 1;
                }
            }
            for (j = 0; j < N; j++) {
                if(numbers[j] == 0){
                    cout << "falta: " << j + 1 << endl;
                    for (int k = 0; k < N; k++) {
                        if(tmp_sol[i+1].items[k] == 0){
                            tmp_sol[i+1].items[k] = j + 1;
                            break;
                        }
                    }
                }
            }



            cout << "3new p1: ";
            for (j = 0; j < N; j++) {
                cout << tmp_sol[i].items[j] << " ";
            }
            cout << endl;
            cout << "3new p2: ";
            for (j = 0; j < N; j++) {
                cout << tmp_sol[i+1].items[j] << " ";
            }
            cout << endl;


            // verificar solución nueva
            // con tmp[i] y tmp[i+1]
            if(!is_in(tmp_sol[i],refset) || !is_in(tmp_sol[i+1],refset)){
                new_sol = true;
                cout << "sol nueva" << endl;
                new_set.push_back(tmp_sol[i]);
                new_set.push_back(tmp_sol[i+1]);
            }
            getchar();
        }
    }

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

bool search_fit(int item, int item_w, int item_h, int &a, int &b, int &h, int **strip){

    bool fit = true;

    for (int y = 0; y < strip_height; y++)
    {
        for (int x = 0; x < strip_width; x++)
        {
            if (strip[x][y]  == 0 && item_w + x - 1 < strip_width) // empty space
            {
                for (b = y; b < y + item_h; b++)
                {
                    for (a = x; a < x + item_w; a++)
                    {
                        //if (strip[a][b] == -1)
                        if (strip[a][b] != 0)
                            fit = false;
                    }
                }
                if (fit){
                    a = x;
                    b = y;
                    if (h < b + item_h){
                        h = b + item_h;
                    }
                    return fit;
                }
            }
            fit = true;
        }
    }
    return false;
}

void place_item(int item, int item_w, int item_h, int a, int b, int **strip){

    int i, j;

    for (i = a; i < a + item_w; i++) {
        for (j = b; j < b + item_h; j++) {
            // strip[i][j] = -1;
            strip[i][j] = item;
        }
    }
}

void print_strip(vector<int> tmp, int h, int **strip){

    const string colors[] = {
            "\e[0;34m",//AZUL
            "\e[0;32m",//VERDE
            "\e[0;36m",//CYAN
            "\e[0;31m",//ROJO
            "\e[0;35m",//PURPURA
            "\e[0;33m",//MARRON
            "\e[0;37m",//GRISCLARO
            "\e[1;33m",//GRISOSCURO
            "\e[1;34m",//AZULCLARO
            "\e[1;32m",//VERDECLARO
            "\e[1;36m",//CYANCLARO
            "\e[1;31m",//ROJOCLARO
            "\e[1;35m",//PURPURACLARO
            "\e[1;33m",//AMARILLO
            "\e[0;37m"//BLANCO
    };

    for (int j = h-1; j >= 0; j--) {
        for (int i = 0; i < strip_width; i++) {

            if ( strip[i][j] != 0){
                for (int k = 0; k < (int)tmp.size(); k++) {
                    if(tmp.at(k) == strip[i][j]){
                        cout << colors[k%14] << strip[i][j] << "\t";
                    }
                }
            }
            else {
                 cout << colors[14] << "#" << "\t";
            }
        }
        cout << endl;
    }

cout << colors[14] << endl;
}

void clear_strip(int **strip){
    for (int ii = 0; ii < strip_width; ii++) {
        for (int jj = 0; jj < strip_height; jj++) {
            strip[ii][jj] = 0;
        }
    }
}

// Bottom-Left approach
void fitness_calculation(vector<solution> &ss){

    int i, j;
    int n = (int)bs.size();
    int item, item_w, item_h;
    int a, b;
    float p;

    for (i = 0; i < popsize; i++)
    {
        ss.at(i).height = 0;
        p = 0.0;
        for (j = 0; j < n; j++)
        {
            a = 0;
            b = 0;
            item   = ss.at(i).items.at(j);
            item_w = bs.at(ss.at(i).items.at(j)-1).width;
            item_h = bs.at(ss.at(i).items.at(j)-1).height;
            if(search_fit(item,item_w,item_h, a, b, ss.at(i).height, ss.at(i).strip)){
                place_item(item,item_w,item_h, a, b, ss.at(i).strip);
            }
            p += item_w * item_h;
        }
        ss.at(i).p = (p*100)/(float)(strip_width * ss.at(i).height);
        //print_strip(ss.at(i).items, ss.at(i).height, ss.at(i).strip);
        ss.at(i).fitness = ss.at(i).p; // TO DO: incluir height
        clear_strip(ss.at(i).strip);
    }
}

void print_solutions(vector<solution> tmp){
    int i, j;

    for (i = 0; i < (int)tmp.size(); i++)
    {
        cout << "Solucion " << i << ":\t";
        for (j = 0; j < (int)bs.size(); j++)
        {
            cout << tmp.at(i).items.at(j) <<  " ";
        }
        cout << " | " << tmp.at(i).height << " | " << tmp.at(i).p << "%" << endl;
    }

}


bool struct_cmp(solution i, solution j){
    return (i.fitness > j.fitness);
}

void sort_solutions(vector<solution> &tmp){
    sort(tmp.begin(), tmp.end(), struct_cmp);
}


void read_input_file(string path){
    ifstream file(path.c_str());
    string value;
    int line_number = 0;
    strip_height=0;
    box tmp;
    while (file.good())
    {
        if (line_number == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                getline(file, value, ',');
            }
        }

        else
        {
            // ID as the line counter
            tmp.id = line_number;

            // Second element "Height"
            getline(file, value, ',');
            tmp.height = atoi(value.c_str());

            // Third element "Width"
            getline(file, value, ',');
            tmp.width = atoi(value.c_str());

            // Empty value
            getline(file, value, ',');
            if(line_number == 1)
            {
                strip_width = atoi(value.c_str());
            }
            strip_height += tmp.height;
            bs.push_back(tmp);
        }

        line_number++;
    }
}

void print_input_file(){
    int i;

    cout << "Strip width: " << strip_width << endl;
    cout << "id\theight\twidth" << endl;
    for(i = 0; i < (int)bs.size(); i++)
    {
        cout << bs.at(i).id << "\t";
        cout << bs.at(i).height << "\t";
        cout << bs.at(i).width << endl;
    }

}

bool check_flags(int argc, char *argv[], string &path){

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h"     , "Shows help message")
        ("input,i"    , po::value<std::string>() , "Path to the input file")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return false;
    }

    if (vm.count("input")) {
        path = vm["input"].as<std::string>();
        cout << "Using input file: " << path << endl;
    } else { cout << "You must set the «input file»" << endl; cout << desc << endl; return false;}


    return true;
}
