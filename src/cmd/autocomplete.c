#include "include/cmd/autocomplete.h"
#include "include/cmd/cmd_history.h"
#include "include/cmd/cmd.h"

#include "include/uart/uart0.h"

atc_buf_ptr *fill_atc_commands(const char *name, size_t *no_of_commands) {
        size_t sz = 0;
        for (size_t j = 0; j < CMDS_BUF_SIZE; j++) {
                if (strpcmp(name, cmds_buf[j].name)) {
                        strcpy(cmds_buf[j].name, atc.atc_buf[sz]);
                        sz++;
                }
        }

        *no_of_commands = sz;
        atc.size = sz;
        atc.idx = 0;

        if (sz > 1) {
                atc.idx_on = true;
//                set_cursor_hidden();
        }

        return (atc_buf_ptr*) &atc.atc_buf;
}

void highlight_next_atc_command(bool clear_previous_output) {
        if (clear_previous_output) {
                clear_autocomplete(false);
        }

        for (int i = 0; i < atc.size; i++) {
                if (atc.idx == i) {
                        uart_puts(ESCAPE_CHARACTER);
                        uart_puts(BG_CODE_WHITE);
                        uart_puts(CMD_COLOR_SEPARATOR);
                        uart_puts(TEXT_CODE_BLACK);
                        uart_puts(END_COLOR_CMD_PREFIX);
                }

                uart_puts(atc.atc_buf[i]);

                if (atc.idx == i) {
                        update_coloscheme();
                }

                if (i != atc.size - 1) {
                        uart_puts(" ");
                }
        }

        atc.idx = (atc.idx + 1) % atc.size;
}

void clear_autocomplete(bool reset_isx_on) {
        for (int i = 0; i < atc.size; i++) {
                clear_n_ch(strlen(atc.atc_buf[atc.size - i - 1]));

                if (i != atc.size - 1) {
                        clear_n_ch(1);
                }
        }

        if (reset_isx_on) {
                atc.idx_on = false;
        }
}

bool is_in_autocomplete() {
        return atc.idx_on;
}

const atc_buf_ptr *get_highlighted_command() {
        return (const atc_buf_ptr*) &atc.atc_buf[(atc.idx - 1) % atc.size];
}