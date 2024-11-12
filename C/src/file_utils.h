/**
 * Author: Max Schessler
 * Date: 2024-11-7
 * 
 * This file holds method signatures for my file handling.
 */

/**
 * This function opens the file specified by the given file path, reads its contents,
 * and returns the contents as a dynamically allocated string. The caller is responsible
 * for freeing the allocated memory.
 * 
 * @param filePath The path to the file to be read.
 * @return A pointer to a dynamically allocated string containing the file contents,
 *         or NULL if the file could not be read.
 */
char *getFileContents(const char *filePath);


/**
 * Reads the contents of a file and returns an array of strings, 
 * where each string represents a line from the file.
 *
 * @param filePath The path to the file to be read.
 * @param numLines A pointer to an integer where the number of lines read will be stored.
 * @return A dynamically allocated array of strings, each representing a line from the file.
 *         The caller is responsible for freeing the memory allocated for the array and its contents.
 */
char **getFileLines(const char *filePath, int *numLines);



/**
 * Splits a given string into an array of strings, each of a specified length.
 *
 * @param s The input string to be split.
 * @param n The length of each split segment.
 * @param length Pointer to int to return to calling scope, number of strings in output array.
 * @return A pointer to an array of strings, where each string is a segment of the input string of length n.
 *         The last segment may be shorter if the length of the input string is not a multiple of n.
 */
char ** lengthSplit(const char *s, int n, int *length);


/**
 * This function iterates through the given string `s` and replaces every instance of `oldChar`
 * with `newChar`.
 * 
 * @param s The string in which the character replacement will occur. It must be a null-terminated string.
 * @param oldChar The character to be replaced.
 * @param newChar The character to replace `oldChar` with.
 */
void replaceChar(char *s, char oldChar, char newChar);

/**
 * @brief Removes all occurrences of a specified character from a string.
 *
 * This function iterates through the given string and removes all instances
 * of the specified character, shifting the remaining characters to the left
 * to fill the gaps.
 *
 * @param s The string from which the character will be removed. This string
 *          is modified in place.
 * @param c The character to be removed from the string.
 */
void removeChar(char *s, char c);


/**
 * Writes a string to a file.
 *
 * @param fileName The name of the file to write to.
 * @param string The string to write to the file.
 * @return An integer indicating success (0) or failure (non-zero).
 */
int writeStringToFile(const char *fileName, const char *string);