#include "include/error/error_code.h"
#include "include/cmd/program/setcolor.h"
#include "include/cmd/cmd.h"
#include "include/string/string.h"
#include "include/cmd/constants.h"
#include "include/cmd/color.h"

#include "include/uart/uart0.h"

err_code flag_setter(const char **args, uint8_t *flags, uint8_t arg_no) {
        if (strcmp(*args, "-t") == 0 && (!arg_no || !(0x1 & *flags))) {
                *flags |= (0x1 << (4 * arg_no));
        } else if (strcmp(*args, "-b") == 0 && (!arg_no || !(0x2 & *flags))) {
                *flags |= (0x2 << (4 * arg_no));
        } else {
                return CMD_INVALID_USAGE;
        }

        return SUCCESS;
}

err_code setcolor_cmd_handler() {
        const char *args = strtok(NULL, CMD_ARGS_SEPARATOR);
        uint8_t flags = 0;

        if (args == NULL) {
                return invalid_cmd_usage(&cmds_buf[SETCOLOR]);
        }

        err_code rtn_val = flag_setter(&args, &flags, 0);
        if (rtn_val != SUCCESS) {
                return invalid_cmd_usage(&cmds_buf[SETCOLOR]);
        }


        args = strtok(NULL, CMD_ARGS_SEPARATOR);
        if (args == NULL) {
                return invalid_cmd_usage(&cmds_buf[SETCOLOR]);
        }

        const color *color1 = find_color(args);
        if (color1 == NULL) {
                uart_puts("Color `");
                uart_puts(args);
                uart_puts("` not found.");
                return CMD_INVALID_USAGE;
        }

        args = strtok(NULL, CMD_ARGS_SEPARATOR);
        if (args == NULL) {
                if (0x1 & flags) {
                        set_text_color(color1);
                } else if (0x2 & flags) {
                        set_bg_color(color1);
                }

                update_coloscheme();
                return SUCCESS;
        }

        rtn_val = flag_setter(&args, &flags, 1);
        if (rtn_val != SUCCESS) {
                return invalid_cmd_usage(&cmds_buf[SETCOLOR]);
        }

        args = strtok(NULL, CMD_ARGS_SEPARATOR);
        if (args == NULL) {
                return invalid_cmd_usage(&cmds_buf[SETCOLOR]);
        }

        const color *color2 = find_color(args);
        args = strtok(NULL, CMD_ARGS_SEPARATOR);
        if (args != NULL) {
                return invalid_cmd_usage(&cmds_buf[SETCOLOR]);
        }

        if (color2 == NULL) {
                uart_puts("Color `");
                uart_puts(args);
                uart_puts("` not found.");
                return CMD_INVALID_USAGE;
        }

        if (0x1 & flags) {
                set_text_color(color1);
                set_bg_color(color2);
        } else {
                set_text_color(color2);
                set_bg_color(color1);
        }

        update_coloscheme();

        return SUCCESS;
}

