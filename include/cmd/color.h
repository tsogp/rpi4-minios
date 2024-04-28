#ifndef ASM2_COLOR_H
#define ASM2_COLOR_H

/*
 * Default colorscheme identifier
*/
#define DEFAULT_COLORSCHEME "0"

/*
 * Color codes for text (foreground)
*/
#define TEXT_CODE_BLACK  "30"
#define TEXT_CODE_RED    "31"
#define TEXT_CODE_GREEN  "32"
#define TEXT_CODE_YELLOW "33"
#define TEXT_CODE_BLUE   "34"
#define TEXT_CODE_PURPLE "38;2;128;0;128"
#define TEXT_CODE_CYAN   "36"
#define TEXT_CODE_WHITE  "37"

/*
* Color codes for background
*/
#define BG_CODE_BLACK   "40"
#define BG_CODE_RED     "41"
#define BG_CODE_GREEN   "42"
#define BG_CODE_YELLOW  "43"
#define BG_CODE_BLUE    "44"
#define BG_CODE_PURPLE  "48;2;128;0;128"
#define BG_CODE_CYAN    "46"
#define BG_CODE_WHITE   "47"

#define TOTAL_COLORS 9

typedef enum color_code {
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_PURPLE,
    COLOR_CYAN,
    COLOR_WHITE,
    COLOR_DEFAULT
} color_code;

typedef struct color {
    const char *name, *text_code, *bg_code;
} color;

/*
 * Array of command colors
 */
static const color colors[] = {
        {"BLACK",    TEXT_CODE_BLACK,     BG_CODE_BLACK},
        {"RED",      TEXT_CODE_RED,       BG_CODE_RED},
        {"GREEN",    TEXT_CODE_GREEN,     BG_CODE_GREEN},
        {"YELLOW",   TEXT_CODE_YELLOW,    BG_CODE_YELLOW},
        {"BLUE",     TEXT_CODE_BLUE,      BG_CODE_BLUE},
        {"PURPLE",   TEXT_CODE_PURPLE,    BG_CODE_PURPLE},
        {"CYAN",     TEXT_CODE_CYAN,      BG_CODE_CYAN},
        {"WHITE",    TEXT_CODE_WHITE,     BG_CODE_WHITE},
        {"DEFAULT",  DEFAULT_COLORSCHEME, DEFAULT_COLORSCHEME}
};

const color *find_color(const char *name);

#endif //ASM2_COLOR_H
