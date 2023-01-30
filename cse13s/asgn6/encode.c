#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include "node.h"
#include "pq.h"
#include "stack.h"
#include "defines.h"
#include "code.h"
#include "io.h"
#include "huffman.h"
#include <unistd.h>
//Help Page
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   This program will encode a file\n"
        "\n"
        "USAGE\n"
        "   %s [-hi:o:v] "
        "-[i: specifies the input], [o: specifies the output], [v: prints statistics], [h: help "
        "page]"
        "\n"
        "OPTIONS\n"
        "   -i         specifies the input file to encode (default: stdin)\n"
        "   -o         specifies the output file to encode (default: stdout)\n"
        "   -v         prints compression statistics to stderr\n"
        "   -h         displays program synopsis and usage\n",
        exec);
}

int main(int argc, char **argv) {
    //Variable declaration & initialization
    int opt = 0;
    bool statistic_output = false;
    char *input_filename = "stdin";
    char *output_filename = "stdout";

    //Organizing user input
    while ((opt = getopt(argc, argv, "b:i:n:d:s:vh")) != -1) {
        switch (opt) {
        case 'i': input_filename = optarg; break;
        case 'o': output_filename = optarg; break;
        case 'v': statistic_output = true; break;
        case 'h': usage(argv[0]); return EXIT_FAILURE;
        default: fprintf(stderr, "incorrect usage please see -H for help\n"); return 1;
        }
    }

    //opening files
    FILE *input_file;
    FILE *output_file;
    input_file = fopen(input_filename, "r");
    output_file = fopen(output_filename, "w");
    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Files failed to open, please try again (see -h for help)");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    return 0;
}
