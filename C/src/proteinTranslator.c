/**
 * Author Max Schessler
 * Date 2024-11-9
 * 
 * This program converts a DNA strand from input file to Protein Strand that is written to output file.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"
#include "protein_utils.h"

void freeAll(char **arr, int numLines);
void convertToRNA(char *sequence);

int main(int argc_count, char **arguments) {
    if (argc_count != 3){
        fprintf(stderr, "ERROR not enough arguments.\nUsage ./proteinTranslator <inputfile> <outputfile>\n");
        return 1;
    }

    char* inputFileName = arguments[1];
    char * outputFileName = arguments[2];

    // get the dna sequence, clean data, split into array of strings of 3 characters for processing
    char *dnaSequence = getFileContents(inputFileName);
    if (dnaSequence == NULL) {
        fprintf(stderr, "ERROR reading from %s\n", inputFileName);
        exit(1);
    }
    convertToRNA(dnaSequence);
    removeChar(dnaSequence, '\n');
    removeChar(dnaSequence, ' ');
    int numOfRnaStrands;
    char **rnaStrand = lengthSplit(dnaSequence, 3, &numOfRnaStrands);
    char *proteinStrand = (char *) malloc(sizeof(char) * numOfRnaStrands + 1);
    char protein;

    // loop over strands of 3 dns chars, make call to rnaToProtein
    int i;
    for (i = 0; i<numOfRnaStrands; i++) {
        protein = rnaToProtein(rnaStrand[i]);
        if (protein == 'x') {
            break;
        }
        proteinStrand[i] = protein;
    }
    proteinStrand[i] = '\0';
    free(dnaSequence);
    freeAll(rnaStrand, numOfRnaStrands);

    writeStringToFile(outputFileName ,proteinStrand);
    free(proteinStrand);

    return 0;

}

void convertToRNA(char *sequence) {
    replaceChar(sequence, 'T', 'U');
}

void freeAll(char **arr, int numLines) {

    if (arr == NULL) {
        printf("Arr is null in freeAll\n");
        return;
    }
    for (int i = 0; i<numLines; i++) {
        if (arr[i] != NULL) {
            free(arr[i]);
        }
    }
    free(arr);
}
