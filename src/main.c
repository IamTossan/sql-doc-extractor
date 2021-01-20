#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/custom-types.h"

const char delimiter[9] = "--  ====";
const int max_line_length = 100;
const int base_padding = 4;

int main(int argc, char const *argv[]) {
    if(argc != 2) {
        printf("incorrect input\n\n");
        printf("usage:\n\tsqlDocExtractor <FILE>\n");
    }

    FILE *inputFile = fopen(argv[1], "r");

    line *extractedDoc = NULL;
    line *start = NULL;

    char line[max_line_length];
    int isDoc = 0;
    while(fgets(line, max_line_length, inputFile) != NULL) {

        if(isDoc) {
            if(strstr(line, delimiter)) {
                break;
            }
            if(!extractedDoc) {
                extractedDoc = makeLine(line + base_padding);
                start = extractedDoc;
            } else {
                extractedDoc->next = makeLine(line + base_padding);
                extractedDoc = extractedDoc->next;
            }
        }

        if(strstr(line, delimiter)) {
            isDoc = 1;
        }
    }

    // DEBUG
    // printLines(start);
    // printf("\n");

    docNode *startDocNode = lineToDocNode(start, 0);

    // DEBUG
    // printDocNode(startDocNode);

    printJson(startDocNode, 0, 4);
    printf("\n");

    fclose(inputFile);
    freeLines(start);
    freeDocNode(startDocNode);
    return 0;
}
