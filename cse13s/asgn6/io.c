#include <unistd.h>
#include <fcntl.h>
#include "code.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h> //DELETE THIS LATER THIS FOR TESTING

extern uint64_t bytes_read;
extern uint64_t bytes_written;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int64_t read_count = 0;
    int64_t current_read_count = 0;

    //looping to read infile
    do {
        current_read_count = read(infile, buf + read_count, nbytes - read_count);
        read_count += current_read_count;
    } while ((read_count < nbytes || nbytes - read_count > 0) && current_read_count != 0);
    return read_count;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int64_t write_count = 0;
    int64_t current_write_count = 0;
    do {
        current_write_count = write(outfile, buf + write_count, nbytes - write_count);
        write_count += current_write_count;
    } while ((write_count < nbytes || nbytes - write_count > 0) && current_write_count != 0);
    return write_count;
}
//Static Variables for read_bit
static uint8_t buffer[BLOCK];
static uint32_t buffer_index = 0;
static uint32_t bit_index = 0;

bool read_bit(int infile, uint8_t *bit) {
    //reading the file if the buffer is empty
    if (buffer_index == 0) {
        bit_index = 0;
        buffer_index = read_bytes(infile, buffer, BLOCK);
    }

    //Returning Bits
    uint8_t current_byte = buffer[buffer_index / 8];
    uint8_t the_bit = current_byte >> (bit_index / 8);
    the_bit &= 0x1;
    bit = &the_bit;

    bit_index++;
    buffer_index -= bit_index / 8;

    //Checking if we read the whole of the buffer
    if (buffer_index == 0) {
        return false;
    } else {
        return true;
    }
}

void write_code(int outfile, Code *c) {
    //If the buffer can still be filled
    for (bit_index = 0; bit_index < code_size(c); bit_index++) {
        //setting bit to 1
        if (code_get_bit(c, bit_index)) {
            buffer[buffer_index / 8] |= (0x1 << (bit_index % 8));
        }
        //setting bit to 0
        else {
            buffer[buffer_index / 8] &= ~(0x1 << (bit_index % 8));
        }
        buffer_index = bit_index / 8;

        //If the buffer is full write to the outfile
        if (buffer_index == BLOCK - 1) {
            buffer_index = 0;
            write_bytes(outfile, buffer, BLOCK);
        }
    }
}

void flush_codes(int outfile) {
    //loops until end of a byte
    while (bit_index % 8 != 0) {
        //setting uninitalized bits to 0
        buffer[buffer_index / 8] &= ~(0x1 << (bit_index % 8));
        bit_index++;
    }
    write_bytes(outfile, buffer, buffer_index);
}
