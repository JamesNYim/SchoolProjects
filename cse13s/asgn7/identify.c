#include "node.h"
#include "pq.h"
#include "ht.h"
#include "bv.h"
#include "bf.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//Help Page
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   This program will decode a file\n"
        "\n"
        "USAGE\n"
        "   %s [-hi:o:v] "
        "-[i: specifies the input], [o: specifies the output], [v: prints statistics], [h: help "
        "page]"
        "\n"
        "OPTIONS\n"
        "   -i         specifies the input file to decode (default: stdin)\n"
        "   -o         specifies the output file to decode (default: stdout)\n"
        "   -v         prints compression statistics to stderr\n"
        "   -h         displays program synopsis and usage\n",
        exec);
}

int main() {

    return 0;
}
