
/**
 * Author Max Schessler
 * Date 2024-11-9
 * 
 * This file holds method definitions for manipulating files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_utils.h"

#define MAX_STRING_LENGTH 2000

char *getFileContents(const char *filePath) {
    if (filePath == NULL) {
        printf("Filepath is null\n");
        return NULL;
    }

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Unable to open %s\n", filePath);
        return NULL;
    }

    // get lengthOfFile in Chars
    fseek(file, 0, SEEK_END); // move file pointer to the end
    int lengthOfFile = ftell(file); // gives us number of characters in the file
    rewind(file); // moves the pointer back to the beginning of the file

    char *string = malloc (sizeof(char) * (lengthOfFile + 1)); // + 1 for null terminator
    if (string == NULL) {
        fprintf(stderr, "Unable to allocate memory\n");
        fclose(file);
        exit(1);
    }
    
    // read every char from file and put it into the char array
    int i = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        string[i] = c;
        i++;
    }

    // set last element to be null terminator
    string[i] = '\0';
    fclose(file);
    return string;
}

char **getFileLines(const char *filePath, int *numLines) {
    if (filePath == NULL || numLines == NULL) {
        printf("ERROR in getFileLines\n");
        return NULL;
    }

    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("ERROR opening %s\n", filePath);
        return NULL;
    }

    // get number of lines by counting \n characters
    int lines = 0;
    char buffer[MAX_STRING_LENGTH];
    while (fgets(buffer, MAX_STRING_LENGTH, file) != NULL) {
        lines ++;
    }

    if (lines == 0) {
        // file is empty 
        fclose(file);
        return NULL;
    }

    // reset file pointer to beginning of file
    rewind(file);

    // create result array of strings
    char **result = (char **) malloc(sizeof(char *) * lines);
    int i = 0;
    int bufferLength;

    printf("Number of lines: %d\n", lines);

    char *s = fgets(buffer, MAX_STRING_LENGTH, file);
    while(s != NULL) {

        // get lenght of buffer
        bufferLength = strlen(buffer);

        // replace newline char with null terminator
        if (buffer[bufferLength-1] == '\n') {
            buffer[bufferLength-1] = '\0';
        }
        result[i] = (char *) malloc(sizeof(char) * bufferLength);
        strcpy(result[i], buffer);
        i++;
        s = fgets(buffer, MAX_STRING_LENGTH, file);
    }

    fclose(file);
    *numLines = lines;
    return result;
}

char ** lengthSplit(const char *s, int n, int *length) {
    // handle null input
    if (s == NULL) {
        printf("ERROR in lengthSplit\n");
        return NULL;
    }

    // handle non integer length of string input
    if (n < 1) {
        printf("ERROR in lengthSplit\n");
        return NULL;
    }

    // get length of the input string and if the input string / n
    // is exactly 1, return a new array of string with one element of a copy of s
    int strLen = strlen(s);
    if (strLen <= n) {
        char ** result = (char **) malloc(sizeof(char *));
        result[0] = (char *) malloc(sizeof(char) * strLen + 1);
        strcpy(result[0], s);
        return result;
    }
    
    // get the total number of strings in the resulting array and create new array
    int numOfStr = (strLen + n - 1) / n;
    int lengthOfEachStr = n;
    int lengthOfLastStr = strLen % n;
    if (lengthOfLastStr == 0) {
        lengthOfLastStr = n;
    }
    char ** result = (char **) malloc (sizeof(char *) * numOfStr);
    if (result == NULL) {
        printf("ERROR allocation for array failed\n");
        return NULL;
    }

    // create a loop that will loop over each element in resulting array
    int i;
    for (i = 0; i < numOfStr - 1; i++) {
        result[i] = (char *) malloc((sizeof(char) * lengthOfEachStr) + 1); // plus one for the \0
        if (result[i] == NULL) {
            for (int k = 0; k < i; k++) {
                free(result[k]);
            }
            free(result);
            printf("ERROR allocating memory for string %d.", i);
            return NULL;
        }

        // copy substring from s to result[i], then add null terminator char at result[i][lengthOfStr + 1]
        // For call to strncpy
        //  Destination: Result[i] current string we are looking at
        //  Source: s + (start - this start is usually 0 for the beginning but will be lengthOfEachStr * i
        //      to begin exactly where we will be copying for this substring of s)
        //  length: length of each string in the array
        strncpy(result[i], s + (lengthOfEachStr * i), lengthOfEachStr);
        result[i][lengthOfEachStr] = '\0'; // set the last char in string to be null terminator
    }

    // add the last string
    result[i] = (char *) malloc((sizeof(char) * lengthOfLastStr) + 1);
    if (result[i] == NULL) {
        for (int k = 0; k < i; k++) {
            free(result[k]);
        }
        free(result);
        printf("ERROR allocating memory for string %d.", i);
        return NULL;
    }
    strncpy(result[i], s + (lengthOfEachStr * i), lengthOfLastStr);
    result[i][lengthOfLastStr] = '\0';

    *length = numOfStr;

    return result;
}

void replaceChar(char *s, char oldChar, char newChar) {
    if (s == NULL) {
        printf("ERROR in replaceChar\n");
        return;
    }
    int length = strlen(s);
    for (int i = 0; i<=length; i++) {
        if (s[i] == oldChar){
            s[i] = newChar;
        }
    }
}

void removeChar(char *s, char c) {
    if (s == NULL) {
        printf("ERROR");
        return;
    }

    int orgLen = strlen(s);
    char * copy = (char *) malloc(sizeof(char) * (orgLen + 1));
    int copyLen = 0;
    for (int i = 0; i<orgLen; i++) {
        if (s[i] != c) {
            // copy this over to current possition
            copy[copyLen] = s[i];
            copyLen ++;
        }
    }
    // copy new string to 
    strcpy(s, copy);
    free(copy);

}

int writeStringToFile(const char *fileName, const char *string) {
    if (fileName == NULL || string == NULL) {
        return 1;
    }

    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        return 1;
    }

    if (fputs(string, file) == EOF) {
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;

}