#include "universe.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <ncurses.h>

#define DELAY 50000

//Help Page
void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   This program is James Yim's version of the Game of Life by John Horton Conway\n"
        "\n"
        "USAGE\n"
        "   %s [-tsn:i:o:H] "
        "-[t: specifies toroidality], [s: silences ncurses], [n: number of generations], [i: input "
        "file], [o: output file]"
        "\n"
        "OPTIONS\n"
        "   -t         specifies if the universe is toroidal\n"
        "   -s         silences ncurses\n"
        "   -n         number of generations. Default: 100\n"
        "   -i         specifies the input file to read to populate the universe. Default: stdin\n"
        "   -o         specifies output file to print the final universe state. Default: stdout\n"
        "   -H         Shows the help page\n",
        exec);
}

int main(int argc, char **argv) {
    int opt = 0;
    bool is_toroidal = false;
    bool ncurses_silence = false;
    uint32_t generations = 100; // default value
    FILE *infile = fopen("stdin", "r");
    FILE *outfile = fopen("stdout", "w");

    //Organizing user input
    while ((opt = getopt(argc, argv, "tsn:i:o:H")) != -1) {
        switch (opt) {
        case 't': is_toroidal = true; break;
        case 's': ncurses_silence = true; break;
        case 'n': generations = strtod(optarg, NULL); break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'H': usage(argv[0]); return EXIT_FAILURE;
        default: fprintf(stderr, "incorrect usage please see -H for help\n"); return 1;
        }
    }

    //Creating initial universe
    uint32_t row = 0;
    uint32_t col = 0;
    fscanf(infile, "%" SCNu32, &row);
    fscanf(infile, "%" SCNu32, &col);
    Universe *current_universe = uv_create(row, col, is_toroidal);
    Universe *next_universe = uv_create(row, col, is_toroidal);
    bool is_populated = uv_populate(current_universe, infile);
    fclose(infile);

    //Checking if universe was successfully populated
    if (!is_populated) {
        fprintf(stderr, "failed to populate universe. Index out of bounds \n");
        return 1;
    }
    //Displaying Generations
    initscr();
    curs_set(false);
    for (uint32_t generation = 0; generation < generations; generation++) {
        clear();

        for (uint32_t i = 0; i < uv_rows(current_universe); i++) {
            for (uint32_t j = 0; j < uv_cols(current_universe); j++) {
                bool is_alive = uv_get_cell(current_universe, i, j);

                //printing current generation
                if (is_alive && !ncurses_silence) {
                    mvprintw(i, j, "o");
                } else if (!ncurses_silence) {
                    mvprintw(i, j, ".");
                }

                //Setting the next universe
                uint32_t num_of_neighbors = uv_census(current_universe, i, j);
                if (is_alive && (num_of_neighbors == 2 || num_of_neighbors == 3)) {
                    uv_live_cell(next_universe, i, j);

                }

                else if (!is_alive && num_of_neighbors == 3) {
                    uv_live_cell(next_universe, i, j);

                } else {
                    uv_dead_cell(next_universe, i, j);
                }
            }
        }
        refresh();
        usleep(DELAY);

        Universe *temp_universe = current_universe;
        current_universe = next_universe;
        next_universe = temp_universe;
    }
    uv_print(current_universe, outfile);
    endwin();
    fclose(outfile);

    uv_delete(current_universe);
    uv_delete(next_universe);
}
