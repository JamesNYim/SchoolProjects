#include <iostream>
#include <fstream>
#include <getopt.h>

#include "grid.h"
#include "util.h"

std::string usage();

#define OPTS "i:o:s:e:p:h"

int main (int const argc, char *argv[]) {
    exec::execname(argv[0]);

    // TODO

    //Getopt
    int opt;

    std::string inputFile;
    std::string outputFile = "-";
    std::string endPoint;
    std::string startPoint;
    std::string imgfile;
    while ((opt = getopt(argc, argv, OPTS)) != -1)
    {
	    switch (opt)
	    {
	        case 'i': inputFile = std::stol(optarg); break;
	        case 'o': outputFile = optarg; break;
                case 's': startPoint = optarg; break;
	        case 'e': endPoint = optarg; break;
                case 'p': imgfile = optarg; break;
   	        case 'h': std::cout << usage(); return 0;
	        default: std::cerr << usage(); return 1;
	    }
    }

    /*    
    //Serializing
    if (outputFile == "-")
    {
	    g.serialize(std::cout);
    }
    else
    {
	    std::ofstream out {outputFile};
	    g.serialize(out);
    }

    //Outputing ppm
    if (imgfile == "-")
    {
	    g.draw(std::cout);
    }
    else if (imgfile.length() > 0)
    {
	    std::ofstream out {imgfile};
	    g.draw(out);
    }
    */

    // Fin
    return exec::status();
}

std::string usage() {
    return std::string{}
        + "SYNOPSIS\n"
        + "     Find the path between two points in a maze\n"
        + "\n"
        + "USAGE\n"
        + "     " + exec::execname() + " [-" + OPTS + "]\n"
        + "\n"
        + "OPTIONS\n"
        + "     -i input.dat        input file with serialized data [default: stdin]\n"
        + "     -o outfile.dat      output file in serialized form [default: stdout]\n"
        + "     -s x:y              starting point for finding path [default: 0:0]\n"
        + "     -e x:y              ending point for finding path [default: bottom right]\n"
        + "     -p img.ppm          generate ppm image of solved maze\n"
        + "     -h                  Print out helpful information\n"
        ;
}
