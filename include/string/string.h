#ifndef ASM2_STRING_H
#define ASM2_STRING_H

#include "include/gpio.h"

/*
 * `strcmp` compares contents of *str1 with contents of *str2
 *
 * @param First string
 * @param Second string
 *
 * @return 0 if strings are equal, 1 if first unequal char of str1 is bigger alphabetically, -1 otherwise
 */
int strcmp(const char *str1, const char *str2);

/*
 * `strpcmp` checks if *str2 contains *str1 as prefix
 *
 * @param Prefix string
 * @param String to look prefix for
 *
 * @return true is *str2 contains *str1 as prefix, false is it does not
 */
bool strpcmp(const char *str1, const char *str2);

/*
 * `strcpy` copies contents of *src to *dest
 *
 * @param String to copy from
 * @param String to copy to
 *
 * @return Pointer to the beginning of the buffer where the src was copied to
 */
char *strcpy(const char *src, char *dest);

/*
 * `strncpy` copies 'n' contents of src to dest
 *
 * @param String to copy from
 * @param String to copy to
 * @param Number of chars to copy
 *
 * @return Pointer to the beginning of the buffer where the *src was copied to
 */
char *strncpy(const char *src, char *dest, size_t n);

/*
 * `strlen` retrieves the length of the string in O(n) complexity
 *
 * @param String to measure length of
 *
 * @return Size of the string
 */
size_t strlen(const char *src);

/*
 * `strcspn` scans *str1 for the first occurrence of the characters that are part of *str2
 *
 * @param String to scan in
 * @param String with chars to look for
 *
 * @return Index of the first occurrence of char from *str2 in *str1
 */
size_t strcspn(const char *str1, const char *str2);

/*
 * `strspn` scans *str1 for initial occurrences of the characters that are part of *str2
 *
 * @param String to scan in
 * @param String with chars to look for
 *
 * @return Size of initial occurrences of chars from *str2 in *str1
 */
size_t strspn(const char *str1, const char *str2);

/*
 * `strtok` split *str into tokens divided with *delimeters
 *
 * @param String to split
 * @param Delimeter string
 *
 * @return Pointer to the beginning of splitter chink
 */
char *strtok(char *str, const char *delimiters);

#endif //ASM2_STRING_H
