#ifndef ASM2_AUTOCOMPLETE_H
#define ASM2_AUTOCOMPLETE_H

#include "include/cmd/cmd.h"
#include "include/string/string.h"
#include "include/cmd/constants.h"

typedef struct autocomplete {
    char atc_buf[CMDS_BUF_SIZE][MAX_COMMAND_SIZE];
    size_t idx, size;
    bool idx_on;
} autocomplete;

static autocomplete atc = {
        {{"\0"}},
        0,
        0,
        false
};

typedef char atc_buf_ptr[MAX_COMMAND_SIZE];

atc_buf_ptr *fill_atc_commands(const char *name, size_t *no_of_commands);

void highlight_next_atc_command(bool clear_previous_output);

void clear_autocomplete(bool reset_isx_on);

bool is_in_autocomplete();

const atc_buf_ptr *get_highlighted_command();

#endif //ASM2_AUTOCOMPLETE_H
