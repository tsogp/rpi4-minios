#ifndef ASM2_CONSTANTS_H
#define ASM2_CONSTANTS_H

/*
 * Erase the character in the shell
*/
#define CHAR_ERASE "\b \b"

/*
 * Move cursor to the left
*/
#define CHAR_MOVE_CURSOR "\b"

/*
 * Move cursor up
*/
#define CHAR_CARRIAGE_RETURN "\r"

/*
 * Buffer size for the command
*/
#define MAX_COMMAND_SIZE 100

/*
 * Buffer size for command history
*/
#define CMD_HISTORY_BUFFER_SIZE 100

/*
 * Backspace key (to identify backspace pressing)
*/
#define BACKSPACE_KEY 127

/*
 * Redefinition of arrow down character
*/
#define ARROW_UP '_'

/*
 * Redefinition of arrow up character
*/
#define ARROW_DOWN '+'

/*
 * ASCII code of newline (\n) character
*/
#define NEWLINE_CHARACTER '\n'

/*
 * Redefinition of TAB character
*/
#define TAB_CHARACTER '\t'

/*
 * Shell prefix
*/
#define SHELL_PREFIX "PavelOS % "

/*
 * Escape character
*/
#define ESCAPE_CHARACTER "\x1b["

/*
 * Cursor to begin of screen character
*/
#define CURSOR_TO_BEGIN_OF_SCREEN "0;0H"

/*
 * Clear screen character
*/
#define CLEAR_SCREEN "2J"

/*
 * Cursor blinking mode
*/
#define CURSOR_BLINKING "25h"

/*
 * Cursor hidden mode
*/
#define CURSOR_HIDDEN "25l"

/*
 * End of color prefix
*/
#define END_COLOR_CMD_PREFIX "m"

/*
 * Color command separator
*/
#define CMD_COLOR_SEPARATOR ";"

/*
 * Color command separator
*/
#define CMD_ARGS_SEPARATOR " "

/*
 * Board revision buffer size
*/
#define BOARD_REVISION_SIZE 8

/*
 * MAC address buffer size
*/
#define MAC_ADDRESS_SIZE 17

/*
 * Welcome string (displayed on startup)
*/
#define WELCOME_STRING  \
                   " ______ ______ ______ _______ ___  _  _   ___   ___  \n"  \
                   "|  ____|  ____|  ____|__   __|__ \\| || | / _ \\ / _ \\ \n"  \
                   "| |__  | |__  | |__     | |     ) | || || (_) | | | |\n"  \
                   "|  __| |  __| |  __|    | |    / /|__  | \\__, | | | |\n"  \
                   "| |____| |____| |____   | |   / /_   | |   / /| |_| |\n"  \
                   "|______|______|______|__|_|  |____|  |_|  /_/  \\___/ \n"  \
                   "|  __ \\ /\\ \\    / /  ____| |       / __ \\ / ____|    \n"  \
                   "| |__) /  \\ \\  / /| |__  | |      | |  | | (___      \n"  \
                   "|  ___/ /\\ \\ \\/ / |  __| | |      | |  | |\\___ \\     \n"  \
                   "| |  / ____ \\  /  | |____| |____  | |__| |____) |    \n"  \
                   "|_| /_/    \\_\\/   |______|______|  \\____/|_____/  \n\n"\
                   "DEVELOPED BY POTEMKIN PAVEL - S3963284\n"
#endif
