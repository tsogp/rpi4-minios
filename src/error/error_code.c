#include "include/error/error_code.h"

const char *get_err_desc(err_code code) {
        static const error err_codes[] = {
                {SUCCESS,         "Success"},
                {CMD_LEN_TOO_BIG, "Command length too big. Please try again."},
                {CMD_NOT_FOUND,   "Command not found. Please try again."}
        };

        return err_codes[code].desc;
}