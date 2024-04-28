#ifndef ASM2_ERROR_CODE_H
#define ASM2_ERROR_CODE_H

/*
 * `err_code` contains the error codes used in the shell
 */
typedef enum err_code {
    /* No error during runtime */
    SUCCESS = 0,

    /* Command size too big */
    CMD_LEN_TOO_BIG = 1,

    /* Command not found */
    CMD_NOT_FOUND = 2,

    /* Command save in history buffer not successful */
    CMD_SV_FAILURE = 3,

    /* Invalid usage of the command */
    CMD_INVALID_USAGE = 4,

    /* Runtime error while execution */
    CMD_RUNTIME_ERROR = 5,
} err_code;

/*
 * `error` combines the error code with a description
 */
typedef struct {
    enum err_code code;
    const char *desc;
} error;

/*
 * `get_err_desc` retrieves the description of an error code
 *
 * @param Error code
 *
 * @return Description of the error code
 */
const char *get_err_desc(err_code code);

#endif //ASM2_ERROR_CODE_H
