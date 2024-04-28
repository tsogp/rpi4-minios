#include "include/cmd/cmd.h"
#include "include/string/string.h"
#include "include/cmd/constants.h"
#include "include/cmd/color.h"

#include "include/uart/uart0.h"

err_code get_command(const char *name, const command **cmd) {
        for (size_t i = 0; i < CMDS_BUF_SIZE; i++) {
                if (strcmp(cmds_buf[i].name, name) == 0) {
                        *cmd = &cmds_buf[i];

                        return SUCCESS;
                }
        }

        return CMD_NOT_FOUND;
}

void move_cursor_n(size_t n) {
        for (int i = 0; i < n; i++) {
                uart_puts(CHAR_MOVE_CURSOR);
        }
}

void clear_n_ch(size_t n) {
        for (size_t i = 0; i < n; i++) {
                uart_puts(CHAR_ERASE);
        }
}

void set_cursor_blinking() {
        uart_puts(ESCAPE_CHARACTER);
        uart_puts(CURSOR_BLINKING);
        uart_puts(END_COLOR_CMD_PREFIX);
}

void set_cursor_hidden() {
        uart_puts(ESCAPE_CHARACTER);
        uart_puts(CURSOR_HIDDEN);
        uart_puts(END_COLOR_CMD_PREFIX);
}

void set_text_color(const color *text_color) {
        cmd_colors.text_color = text_color;
}

void set_bg_color(const color *bg_color) {
        cmd_colors.bg_color = bg_color;
}

void update_coloscheme() {
        uart_puts(ESCAPE_CHARACTER);

        if (strcmp(cmd_colors.bg_color->bg_code, DEFAULT_COLORSCHEME) != 0 && strcmp(cmd_colors.text_color->text_code, DEFAULT_COLORSCHEME) == 0) {
                uart_puts(cmd_colors.text_color->text_code);
                uart_puts(CMD_COLOR_SEPARATOR);
                uart_puts(cmd_colors.bg_color->bg_code);
        } else {
                uart_puts(cmd_colors.bg_color->bg_code);
                uart_puts(CMD_COLOR_SEPARATOR);
                uart_puts(cmd_colors.text_color->text_code);
        }

        uart_puts(END_COLOR_CMD_PREFIX);
}

err_code invalid_cmd_usage(const command *cmd) {
        uart_puts("Invalid usage.\n\n");
        uart_puts(cmd->desc);
        return CMD_INVALID_USAGE;
}

void print_shell_prefix(err_code code) {
        uart_puts("\n");

        uart_puts(ESCAPE_CHARACTER);
        uart_puts(DEFAULT_COLORSCHEME);
        uart_puts(CMD_COLOR_SEPARATOR);
        if (code != SUCCESS) {
                uart_puts(TEXT_CODE_RED);
        } else {
                uart_puts(TEXT_CODE_GREEN);
        }

        uart_puts(END_COLOR_CMD_PREFIX);
        uart_dec(code);
        uart_puts(" ");
        update_coloscheme();
        uart_puts(SHELL_PREFIX);
}