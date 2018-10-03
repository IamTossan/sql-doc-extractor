#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/custom-types.h"

const char delimiter[9] = "--  ====";
const int max_line_length = 100;

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
                extractedDoc = makeLine(line + 4);
                start = extractedDoc;
            } else {
                extractedDoc->next = makeLine(line + 4);
                extractedDoc = extractedDoc->next;
            }
        }

        if(strstr(line, delimiter)) {
            isDoc = 1;
        }
    }

    // displayLines(start);

    docNode *startDocNode = lineToDocNode(start);
    // displayDocNode(startDocNode);
    toJson(startDocNode);

    fclose(inputFile);
    freeLines(start);
    freeDocNode(startDocNode);
    return 0;
}
