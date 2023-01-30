

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "universe.h"

//Defines what a Universe has
struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

//Creates a Universe
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *u = (Universe *) malloc(sizeof(Universe *));
    u->grid = (bool **) calloc(rows, sizeof(bool *));
    for (uint32_t row = 0; row < rows; row++) {
        u->grid[row] = (bool *) calloc(cols, sizeof(bool));
    }
    u->rows = rows;
    u->cols = cols;
    u->toroidal = toroidal;
    //u->grid = **matrix;
    return u;
}

//Deletes a Universe freeing memory
void uv_delete(Universe *u) {
    for (uint32_t i = 0; i < uv_rows(u); i++) {
        free(u->grid[i]);
        u->grid[i] = NULL;
    }
    free(u->grid);
    u->grid = NULL;
    free(u);
    u = NULL;
}

//Gives the amount of rows in a Universe
uint32_t uv_rows(Universe *u) {
    return u->rows;
}

//Gives the amount of columns in a Universe
uint32_t uv_cols(Universe *u) {
    return u->cols;
}

//Sets cell to be alive
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r >= 0 && r < uv_rows(u) && c >= 0 && c < uv_cols(u)) {
        u->grid[r][c] = true;
    }
}

//Sets cell to be dead
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r >= 0 && r < uv_rows(u) && c >= 0 && c < uv_cols(u)) {
        u->grid[r][c] = false;
    }
}

//Checks to see if cell is alive or dead
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    if (r >= 0 && r < uv_rows(u) && c >= 0 && c < uv_cols(u)) {

        return u->grid[r][c];
    }
    return -1;
}

//Puts live cells in the Universe
bool uv_populate(Universe *u, FILE *infile) {
    uint32_t in_row = uv_rows(u);
    uint32_t in_col = uv_cols(u);
    while (fscanf(infile, "%" SCNu32, &in_row) && fscanf(infile, "%" SCNu32, &in_col) != EOF) {
        if (in_col > uv_cols(u) || in_row > uv_rows(u) || in_col < 0 || in_row < 0) {
            return false;
        }
        uv_live_cell(u, in_row, in_col);
    }
    return true;
}

//Checks the neighbor cells
uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    uint32_t amount_of_neighbors = 0;
    uint32_t row_index = 0;
    uint32_t col_index = 0;
    uint32_t starting_row = 0;
    uint32_t starting_col = 0;

    if (r >= 0 && r < uv_rows(u) && c >= 0 && c < uv_cols(u)) {
        //Toroidal Universe
        if (u->toroidal) {
            uint32_t rows_checked = 0;
            row_index = (r + uv_rows(u) - 1) % uv_rows(u);
            col_index = (c + uv_cols(u) - 1) % uv_cols(u);
            for (row_index = (r + uv_rows(u) - 1) % uv_rows(u); rows_checked < 3;
                 row_index = ((row_index + 1) % uv_rows(u))) {
                uint32_t cols_checked = 0;
                for (col_index = (c + uv_cols(u) - 1) % uv_cols(u); cols_checked < 3;
                     col_index = ((col_index + 1) % uv_cols(u))) {
                    if (!(row_index == r && col_index == c)
                        && uv_get_cell(u, row_index, col_index)) {
                        amount_of_neighbors++;
                    }
                    cols_checked++;
                }
                rows_checked++;
            }

        }

        //Non-toroidal Universe
        else {
            if (r == 0) {
                starting_row = r;
            } else {
                starting_row = r - 1;
            }
            if (c == 0) {
                starting_col = c;
            } else {
                starting_col = c - 1;
            }
            for (uint32_t i = starting_row; i <= r + 1; i++) {
                for (uint32_t j = starting_col; j <= c + 1; j++) {
                    if (uv_get_cell(u, i, j) && !(i == r && j == c)) {
                        amount_of_neighbors++;
                    }
                }
            }
        }
        return amount_of_neighbors;
    }
    return -1;
}

//Prints the current Universe generation
void uv_print(Universe *u, FILE *outfile) {
    for (uint32_t i = 0; i < uv_rows(u); i++) {
        for (uint32_t j = 0; j < uv_cols(u); j++) {
            if (uv_get_cell(u, i, j)) {
                fprintf(outfile, "o");
            } else {
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n");
    }
}
