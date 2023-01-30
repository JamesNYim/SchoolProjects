#include <iostream>
#include <fstream>
#include <getopt.h>

#include "grid.h"
#include "util.h"

std::string usage();

#define OPTS "i:o:p:h"

int main(int const argc, char *argv[]) {
    exec::execname(argv[0]);

    // TODO

    // Fin
    return exec::status();
}

std::string usage() {
    return std::string{}
        + "SYNOPSIS\n"
        + "     Given a randomized \"grid-graph\", generate a maze by creating a\n"
        + " minimum spanning tree\n"
        + "\n"
        + "USAGE\n"
        + "     " + exec::execname() + " [-" + OPTS + "]\n"
        + "\n"
        + "OPTIONS\n"
        + "     -i infile           input file with serialized grid data [default: stdin]\n"
        + "     -o outfile          maze output in serialized form [default: stdout]\n"
        + "     -p img.ppm          generate ppm image of maze\n"
        + "     -h                  Print out helpful information\n"
        ;
}
