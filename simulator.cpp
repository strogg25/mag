#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "boost/program_options.hpp"
#include "environment.h"
using namespace std;

int main(int argc, char* argv[]){

    int seed = 0;
    bool verbose = false;

    namespace po = boost::program_options;
    po::options_description desc("Options");
    desc.add_options()
      ("seed,s", po::value<int>(), "Seed for the random generator")
      ("verbose,v", "Print diagnostic informations");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("seed")){
      seed = vm["seed"].as<int>();
    }

    if (vm.count("verbose")){
      verbose = true;
    }

    //Initialize the random generator.
    srand(seed);

    Environment environment;

    //Initialize the environment.
    string _chromosome = "A";
    environment.initialization(_chromosome, verbose, seed);

    //Run the main loop.
    environment.main_loop();

    return 0;
}
