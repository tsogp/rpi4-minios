#include "include/error/error_code.h"
#include "include/cmd/program/help.h"
#include "include/string/string.h"
#include "include/utils/size.h"
#include "include/cmd/constants.h"
#include "include/cmd/cmd.h"

#include "include/uart/uart0.h"

err_code help_cmd_handler() {
        const char *cmd_name = strtok(NULL, CMD_ARGS_SEPARATOR);

        if (cmd_name == NULL) {
                uart_puts(HELP_DESC_BRIEF);
                return SUCCESS;
        }

        const command *cmd = NULL;
        err_code rslt = get_command(cmd_name, &cmd);

        if (strtok(NULL, CMD_ARGS_SEPARATOR) != NULL) {
                return invalid_cmd_usage(&cmds_buf[HELP]);
        }

        if (rslt != SUCCESS) {
                uart_puts("Command `");
                uart_puts(cmd_name);
                uart_puts("` not found.");
                return rslt;
        }

        uart_puts(cmd->desc);
        return rslt;
}

