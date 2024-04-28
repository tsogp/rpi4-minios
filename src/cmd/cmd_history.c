#include "include/cmd/cmd_history.h"
#include "include/string/string.h"
#include "utils/size.h"
#include "include/cmd/cmd.h"

#include "include/uart/uart0.h"

err_code save_command(const char *cmd, bool reset_history_idx) {
        char *save = strcpy(
                cmd,
                history.hbuf[history.lidx]
        );

        history.hbuf[history.lidx][strlen(cmd)] = '\0';

        history.tsaved =
                (history.tsaved == CMD_HISTORY_BUFFER_SIZE)
                ? history.tsaved
                : history.tsaved + 1;

        history.lidx = (history.lidx + 1) % CMD_HISTORY_BUFFER_SIZE;

        if (reset_history_idx) {
                history.hidx = 0;
                history.bhist = false;
        }

        return (save != NULL)
               ? SUCCESS
               : CMD_SV_FAILURE;
}

bool is_viewing_history() {
        return history.bhist == true;
}

bool is_buffer_full() {
        return history.tsaved == CMD_HISTORY_BUFFER_SIZE;
}

const char* get_prev_command() {
        if (history.bhist < history.tsaved) {
                history.bhist++;

                uint16_t idx = (history.lidx >= history.bhist)
                        ? history.lidx - history.bhist
                        : history.tsaved - (history.bhist - history.lidx);

//                uart_puts("\n\nget_prev_command: bhist: ");
//                uart_dec(history.bhist);
//                uart_puts("\nlidx: ");
//                uart_dec(history.lidx);
//                uart_puts("\ntsaved: ");
//                uart_dec(history.tsaved);
//                uart_puts("\nidx: ");
//                uart_dec(idx);
//                uart_puts("\n\n");


                return history.hbuf[idx];
        }

        return NULL;
}

const char* get_next_command() {
//        uart_puts("\n\nget_next_command: bhist: ");
//        uart_dec(history.bhist);
//        uart_puts("\nlidx: ");
//        uart_dec(history.lidx);
//        uart_puts("\ntsaved: ");
//        uart_dec(history.tsaved);
//        uart_puts("\n\n");

        if (history.bhist > 1) {
                history.bhist--;

                uint16_t idx = (history.lidx >= history.bhist)
                               ? history.lidx - history.bhist
                               : history.tsaved - (history.bhist - history.lidx);

//                uart_puts("\n\nget_next_command: bhist: ");
//                uart_dec(history.bhist);
//                uart_puts("\nlidx: ");
//                uart_dec(history.lidx);
//                uart_puts("\ntsaved: ");
//                uart_dec(history.tsaved);
//                uart_puts("\nidx: ");
//                uart_dec(idx);
//                uart_puts("\n\n");

                return history.hbuf[idx];
        }

        return NULL;
}

void print_or_skip_command(uint8_t *idx, const char*(get_cmd)(), char* buf) {
//        if (!is_viewing_history() && get_cmd == get_prev_command) {
//                uart_puts("\ncommand saved\n");
//
//                save_command(buf, false);
//                history.bhist = true;
//        }

//        uart_puts("\n\nbhist: ");
//        uart_dec(history.bhist);
//        uart_puts("\nlidx: ");
//        uart_dec(history.lidx);
//        uart_puts("\ntsaved: ");
//        uart_dec(history.tsaved);
//        uart_puts("\n\n");

        const char* command = get_cmd();

        if (command != NULL) {
                strcpy(command, buf);
                clear_n_ch(*idx);
                *idx = strlen(command);
                uart_puts(command);
        }
}

const char* get_last_saved_command() {
        return (history.lidx != 0)
                ? history.hbuf[history.lidx - 1]
                : (history.tsaved == CMD_HISTORY_BUFFER_SIZE)
                        ? history.hbuf[history.tsaved - 1]
                        : NULL;
}

