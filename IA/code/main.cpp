#include "utils.cpp"

int main(int argc, char *argv[]) {

    string path;
    if(!check_flags(argc,argv,path)){
        return 1;
    }
    read_input_file(path);
    print_input_file();

    // body

    return 0;
}
