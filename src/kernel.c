#include "include/gpio.h"
#include "include/error/error_code.h"
#include "include/cmd/constants.h"
#include "include/cmd/cmd.h"
#include "include/cmd/cmd_history.h"
#include "include/string/string.h"
#include "include/cmd/autocomplete.h"
#include "include/uart/uart0.h"

void handle_cli_input() {
        static char cmd_buffer[MAX_COMMAND_SIZE + 1];
        static uint8_t idx;

        unsigned char c = uart_getc();
        err_code exec_res = SUCCESS;

        switch (c) {
                case BACKSPACE_KEY: {
                        if (!is_in_autocomplete()) {
                                if (idx > 0) {
                                        uart_puts(CHAR_ERASE);
                                        cmd_buffer[--idx] = '\0';
                                }
                        } else {
                                clear_autocomplete(true);
                                uart_puts(cmd_buffer);
                        }

                        break;
                }
                case NEWLINE_CHARACTER: {
                        if (is_in_autocomplete()) {
                                strcpy((const char *) get_highlighted_command(), cmd_buffer);
                                clear_autocomplete(true);

                                idx = strlen(cmd_buffer);
                                cmd_buffer[idx] = '\0';

                                uart_puts(cmd_buffer);

                        }

                        if (idx > 0) {
                                uart_puts("\n");

                                if (idx >= MAX_COMMAND_SIZE) {
                                        uart_puts(get_err_desc(CMD_LEN_TOO_BIG));
                                        print_shell_prefix(CMD_LEN_TOO_BIG);

                                        idx = 0;

                                        return;
                                }

                                if (idx != 0 && strcmp(cmd_buffer, get_last_saved_command()) != 0) {
                                        save_command(cmd_buffer, true);
                                }

                                char *cmd = strtok(cmd_buffer, CMD_ARGS_SEPARATOR);

                                const command *cmd_ptr = NULL;
                                err_code is_cmd_found = get_command(cmd, &cmd_ptr);
                                if (is_cmd_found == SUCCESS) {
                                        exec_res = cmd_ptr->handler();
                                } else {
                                        exec_res = is_cmd_found;
                                        uart_puts(get_err_desc(is_cmd_found));
                                }
                        }


                        print_shell_prefix(exec_res);
                        idx = 0;
                        cmd_buffer[idx] = '\0';
                        break;
                }
                case ARROW_UP: {
                        print_or_skip_command(&idx, get_prev_command, cmd_buffer);
                        break;
                }
                case ARROW_DOWN: {
                        print_or_skip_command(&idx, get_next_command, cmd_buffer);
                        break;
                }
                case TAB_CHARACTER: {
                        if (!is_in_autocomplete()) {
//                                uart_puts(cmd_buffer);
//                                uart_puts("\n");

                                size_t no_commands_found;
                                atc_buf_ptr *cmds = fill_atc_commands(cmd_buffer, &no_commands_found);
                                if (no_commands_found > 1) {
                                        clear_n_ch(idx);
                                        highlight_next_atc_command(false);
                                } else if (no_commands_found == 1) {
                                        uart_puts(cmds[0] + idx);
                                        strcpy(cmds[0] + idx, cmd_buffer + idx);
                                        idx += strlen(cmds[0] + idx);
                                }
                        } else {
                                highlight_next_atc_command(true);
                        }

                        break;
                }
                default: {
                        if (!is_in_autocomplete()) {
                                if (idx < MAX_COMMAND_SIZE) {
                                        cmd_buffer[idx] = c;
                                        cmd_buffer[idx + 1] = '\0';
                                }

                                uart_sendc(c);
                                idx++;
                        }
                }
        }
}

void main() {
        uart_init();
        uart_puts(WELCOME_STRING);
        print_shell_prefix(SUCCESS);

        while (1) {
                handle_cli_input();
        }
}