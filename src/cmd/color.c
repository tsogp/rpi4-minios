#include "include/cmd/color.h"
#include "include/gpio.h"
#include "include/string/string.h"
#include "include/utils/size.h"

const color *find_color(const char *name) {
        for (size_t i = 0; i < TOTAL_COLORS; i++) {
                if (strcmp(colors[i].name, name) == 0) {
                        return &colors[i];
                }
        }

        return NULL;
}