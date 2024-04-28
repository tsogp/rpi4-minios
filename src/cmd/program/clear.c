#include "include/error/error_code.h"
#include "include/cmd/program/clear.h"
#include "include/cmd/constants.h"
#include "include/string/string.h"
#include "include/utils/size.h"
#include "include/cmd/cmd.h"

#include "include/uart/uart0.h"

err_code clear_cmd_handler() {
        if (strtok(NULL, CMD_ARGS_SEPARATOR) != NULL) {
                return invalid_cmd_usage(&cmds_buf[CLEAR]);
        }

        uart_puts(ESCAPE_CHARACTER);
        uart_puts(CURSOR_TO_BEGIN_OF_SCREEN);
        uart_puts(ESCAPE_CHARACTER);
        uart_puts(CLEAR_SCREEN);

        return SUCCESS;
}

