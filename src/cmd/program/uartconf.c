#include "include/cmd/program/uartconf.h"
#include "include/uart/uart0.h"
#include "include/string/string.h"
#include "include/utils/size.h"
#include "include/cmd/constants.h"
#include "include/cmd/cmd.h"
#include "include/uart/config.h"

err_code fill_config_argument(const arg_config **dest, const arg_config *(*find_arg_func)(const char*), const char *setting) {
        const char *value = strtok(NULL, CMD_ARGS_SEPARATOR);
        if (*dest != NULL || value == NULL) {
                return CMD_INVALID_USAGE;
        }

        *dest = find_arg_func(value);
        if (*dest == NULL) {
                uart_puts(value);
                uart_puts(" is not valid value for ");
                uart_puts(setting);
                uart_puts(".");
                return CMD_INVALID_USAGE;
        }

        return SUCCESS;
}

err_code uartconf_cmd_handler() {
        const char *args = strtok(NULL, CMD_ARGS_SEPARATOR);
        if (args == NULL) {
                return invalid_cmd_usage(&cmds_buf[UARTCONF]);
        }

        err_code rtn_val = CMD_INVALID_USAGE;
        uint32_t baud_rate = 0;
        const arg_config *data_bit = NULL, *stop_bit = NULL, *parity = NULL, *handshake = NULL;

        for (uint8_t i = 0; args != NULL && i < 5; i++) {
                if (strcmp(args, "-b") == 0) {
                        args = strtok(NULL, CMD_ARGS_SEPARATOR);
                        if (args == NULL) {
                                return invalid_cmd_usage(&cmds_buf[UARTCONF]);
                        }

                        for (const char *c = args; *c != '\0'; c++) {
                                if (*c < 48 || *c > 57) {
                                        uart_puts("Baud Rate value must be positive numeric.");
                                        return CMD_INVALID_USAGE;
                                }

                                baud_rate *= 10;
                                baud_rate += (*c - '0');
                        }

                        rtn_val = SUCCESS;
                } else if (strcmp(args, "-d") == 0) {
                        rtn_val = fill_config_argument(&data_bit, find_data_bits_args, "data bits");
                } else if (strcmp(args, "-s") == 0) {
                        rtn_val = fill_config_argument(&stop_bit, find_stop_bits_args, "stop bits");
                } else if (strcmp(args, "-p") == 0) {
                        rtn_val = fill_config_argument(&parity, find_parities_args, "parity");
                } else if (strcmp(args, "-h") == 0) {
                        rtn_val = fill_config_argument(&handshake, find_handshakes_args, "handshake");
                }

                if (rtn_val != SUCCESS) {
                        return rtn_val;
                }

                rtn_val = CMD_INVALID_USAGE;
                args = strtok(NULL, CMD_ARGS_SEPARATOR);
        }

        if (args != NULL) {
                return invalid_cmd_usage(&cmds_buf[UARTCONF]);
        }

        update_config(baud_rate, data_bit, stop_bit, parity, handshake);
        uart_init();
        return SUCCESS;
}