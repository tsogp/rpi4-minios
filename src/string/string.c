#include "include/string/string.h"
#include "include/utils/size.h"

int strcmp(const char *str1, const char *str2) {
        while (*str1 && (*str1 == *str2)) { ;
                str1++;
                str2++;
        }

        return *(const unsigned char *) str1 - *(const unsigned char *) str2;
}

char *strcpy(const char *src, char *dest) {
        char *bgn = dest;
        for (; (*dest = *src); dest++, src++);
        return bgn;
}

bool strpcmp(const char *str1, const char *str2) {
        while (*str1 && (*str1 == *str2)) {
                str1++;
                str2++;
        }

        return *str1
                ? false
                : true;
}

char *strncpy(const char *src, char *dest, size_t n) {
        char *bgn = dest;
        for (size_t i = 0; (*dest = *src) && i < n; dest++, src++, i++);
        return bgn;
}

size_t strlen(const char *src) {
        const char* s;
        for (s = src; *s; s++);
        return s - src;
}

size_t strcspn(const char *str1, const char *str2) {
        size_t idx = 0;
        for (const char *p1 = str1; *p1; p1++) {
                for (const char *p2 = str2; *p2; p2++) {
                        if (*p1 == *p2) {
                                return idx;
                        }
                }
                idx++;
        }

        return idx;
}

size_t strspn(const char *str1, const char *str2) {
        size_t count = 0;
        for (const char *p1 = str1; *p1; p1++) {
                const char *p2;
                for (p2 = str2; *p2; p2++) {
                        if (*p1 == *p2) {
                                break;
                        }
                }

                if (*p2 == '\0') {
                        return count;
                } else {
                        ++count;
                }
        }

        return count;
}


char *strtok(char *str, const char *delimiters) {
        static char *p;

        if (str != NULL) {
                p = str;
        }

        if (p == NULL) {
                return NULL;
        }

        p += strspn(p, delimiters);

        if (*p == '\0') {
                p = NULL;
                return p;
        } else {
                char *start = p;
                p += strcspn(p, delimiters);
                if (*p == '\0') {
                        p = NULL;
                } else {
                        *p++ = '\0';
                }

                return start;
        }
}