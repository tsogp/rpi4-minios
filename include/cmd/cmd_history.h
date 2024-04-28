#ifndef ASM2_CMD_HISTORY_H
#define ASM2_CMD_HISTORY_H

#include "constants.h"
#include "include/gpio.h"
#include "include/error/error_code.h"

/*
 * `cmd_history` structure is used to handle the command history in the shell
*/
typedef struct {
    /* `hbuf` - 'history buffer' - buffer to save the commands */
    char hbuf[CMD_HISTORY_BUFFER_SIZE][MAX_COMMAND_SIZE + 1];

    /* `lidx` - 'last index' - points to the spot to the next command */
    uint16_t lidx;

    /* `tsaved` - 'total saved' - total number of commands saved */
    uint16_t tsaved;

    /* `hidx` - 'history index' - points to the current command viewed from the history buffer from the end */
    uint16_t hidx;

    /* `bhist` - 'browsing history' - true is currently browsing history (ARROW_LEFT was pressed) */
    bool bhist;

    /* `bend` - 'buffer end' - true if continious ARROW_LEFT pressing reached first command in buffer */
    bool bend;
} cmd_history;

/*
 * global `cmd_history` object to manage shell history
*/
static cmd_history history = {
        {"\0"},
        0,
        0,
        0,
        false,
        false,
};

/*
 * `save_command` saves command in buffer
 *
 * @param Command literal to be saved
 * @param Flag if `hidx` should be reset
*/
err_code save_command(const char *cmd, bool reset_history_idx);

/*
 * `get_prev_command` retrieves the older command (saved longer time ago)
 *
 * @return Command string literal
*/
const char *get_prev_command();

/*
 * `get_next_command` retrieves the newer command (saved shorter time ago)
 *
 * @return Command string literal
*/
const char *get_next_command();

/*
 * `print_or_skip_command` prints out the command if user is viewing history and no buffer limits are met
 * (user is not at the rightmost or leftmost command)
 *
 * @param Index to the current command in the buffer
 * @param Function to retrieve the command
 * @param Buffer for the last typed command
*/
void print_or_skip_command(uint8_t *idx, const char *(get_cmd)(), char *buf);

/*
 * `get_last_saved_command` retrieves the last command saved in buffer
 *
 * @return Last saved command string literal
*/
const char* get_last_saved_command();

#endif
