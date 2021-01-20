#include <stdio.h>
#include <stdlib.h>

#include "doc_tree.h"

docNode* makeDocNode(char *key, char *type, char *value) {
    docNode *i = malloc(sizeof(docNode));
    i->key = key;
    i->type = type;
    i->value = value;
    i->children = NULL;
    i->next = NULL;
    return i;
}


void printDocNode(docNode *start) {
    docNode *current = start;
    while(current != NULL) {
        printf("key: %s\n", current->key);
        if(current->children != NULL) {
            printf("\nchildren of %s:\n\n", current->key);
            printDocNode(current->children);
        } else {
            if(current->type != NULL) {
                printf("type: %s\n", current->type);
            }
            printf("value: %s\n", current->value);
        }
        printf("\n");
        current = current->next;
    }
}

void freeDocNode(docNode *start) {
    docNode *current = start;
    while(current != NULL) {
        if(current->children) {
            freeDocNode(current->children);
        }
        docNode *next = current->next;
        free(current);
        current = next;
    }
}

void printPadding(int n) {
    for(int i = 0; i < n; i++) {
        printf(" ");
    }
}

void printJson(docNode *start, int padding, int paddingStep) {
    docNode *i = start;
    int basePadding = padding + paddingStep;

    printf("{\n");

    while(i != NULL) {

        if(i->children != NULL) {
            printPadding(basePadding);
            printf("\"%s\": ", i->key);

            printJson(i->children, basePadding, paddingStep);
        } else if(i->type != NULL) {
            printPadding(basePadding);
            printf("\"%s\": {\n", i->key);

            printPadding(basePadding + paddingStep);
            printf("\"type\": \"%s\",\n", i->type);
            printPadding(basePadding + paddingStep);
            printf("\"value\": \"%s\"\n", i->value);

            printPadding(basePadding);
            printf("}");
        } else {
            printPadding(basePadding);
            printf("\"%s\": \"%s\"", i->key, i->value);
        }

        if(i->next != NULL) {
            printf(",");
        }

        printf("\n");
        i = i->next;
    }
    printPadding(padding);
    printf("}");
}
