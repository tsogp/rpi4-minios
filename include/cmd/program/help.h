#ifndef ASM2_HELP_H
#define ASM2_HELP_H

#define HELP_NAME "help"

#define HELP_DESC \
        "Usage: help <[COMMAND]>\n" \
        "Get brief description of all commands or full description of [COMMAND]\n\n" \
        " [COMMAND]         name of the command to get description from\n\n" \
        "Examples:\n" \
        "  help help        Get help (this program) description\n" \
        "  help showinfo    Get showinfo (other program) description\n"

#define HELP_DESC_BRIEF \
        "Brief description and examples of available commands: \n\n" \
        "  help                                                - Show brief information of all commands\n" \
        "  help [COMMAND]                                      - Show full information of the command\n" \
        "  clear                                               - Clear screen\n" \
        "  setcolor -t [TEXT_COLOR] -b [BACKGROUND_COLOR]      - Set text color, and/or background color\n" \
        "  showinfo                                            - Show board revision and board MAC address\n"

err_code help_cmd_handler();

#endif
