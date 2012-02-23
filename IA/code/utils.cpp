#include "utils.hpp"

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
