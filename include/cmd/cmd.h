#ifndef ASM2_CMD_H
#define ASM2_CMD_H

#include "include/error/error_code.h"
#include "include/gpio.h"

#include "include/cmd/program/clear.h"
#include "include/cmd/program/help.h"
#include "include/cmd/program/setcolor.h"
#include "include/cmd/program/showinfo.h"
#include "include/cmd/program/uartconf.h"
#include "include/utils/size.h"
#include "include/cmd/color.h"

/*
 * `cmd_handler` is a generic interface of a function called when a command is executed
 *
 * @param Command arguments
 *
 * @return Error code
 */
typedef enum err_code (*cmd_handler)();

typedef enum cmd_id {
    CLEAR = 0,
    HELP = 1,
    SETCOLOR = 2,
    SHOWINFO = 3,
    UARTCONF = 4,
} cmd_id;

/*
 * `command` combines command name, description and handler
 */
typedef struct command {
    const char *name;
    const char *desc;
    cmd_handler handler;
} command;

/*
 * `get_command` Looks for the command based on the *name and writes its value into **cmd if found
 *
 * @param Command name
 * @param Structure reference to write command to
 *
 * @return Error code
 */
err_code get_command(const char *name, const command **cmd);

/*
 * `cmds_buf` Buffer for all commands accessible from the shell
 */
static const command cmds_buf[] = {
        {CLEAR_NAME, CLEAR_DESC, clear_cmd_handler},
        {HELP_NAME, HELP_DESC, help_cmd_handler},
        {SETCOLOR_NAME, SETCOLOR_DESC, setcolor_cmd_handler},
        {SHOWINFO_NAME, SHOWINFO_DESC, showinfo_cmd_handler},
        {UARTCONF_NAME, UARTCONF_DESC, uartconf_cmd_handler},
};

typedef struct cmd_color {
    const color *text_color, *bg_color;
} cmd_color;

static cmd_color cmd_colors = {
        &colors[COLOR_DEFAULT],
        &colors[COLOR_DEFAULT]
};

/*
 * Size of the commands buffer
*/
#define CMDS_BUF_SIZE SZ(cmds_buf, command)

void move_cursor_n(size_t n);

/*
 * `clear_n_ch` clears `n` characters from the shell
 *
 * @param Number of characters to be erased
*/
void clear_n_ch(size_t n);

void set_text_color(const color *text_color);

void set_bg_color(const color *bg_color);

void set_cursor_blinking();

void set_cursor_hidden();

void update_coloscheme();

err_code invalid_cmd_usage(const command *cmd);

void print_shell_prefix(err_code code);

#endif
