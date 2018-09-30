#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char delimiter[9] = "--  ====";
const int max_line_length = 100;

// extractedDoc
typedef struct line {
    char *text;
    struct line *next;
} line;

line* makeLine(char *text) {
    line *l = malloc(sizeof(line));
    l->text = strdup(text);
    l->next = NULL;
    return l;
}

void displayLines(line *start) {
    line *current = start;
    while(current != NULL) {
        printf("%s", current->text);
        current = current->next;
    }
}

void deleteLines(line *start) {
    line *current = start;
    while(current != NULL) {
        line *next = current->next;
        free(current->text);
        free(current);
        current = next;
    }
}

//docTree
typedef struct docTree {
    char *key;
    char *type;
    struct docTree *children;
    struct docTree *next;
} docTree;

docTree* makeDocTree(char *key, char *type) {
    docTree *i = malloc(sizeof(docTree));
    i->key = strdup(key);
    i->type = strdup(type);
    i->children = NULL;
    i->next = NULL;
    return i;
}

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

    displayLines(start);

    fclose(inputFile);
    deleteLines(start);
    return 0;
}
