#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "custom-types.h"

// line

line* makeLine(char *text) {
    line *l = malloc(sizeof(line));
    l->text = strdup(text);
    l->next = NULL;
    l->text[strlen(l->text) - 1] = '\0';
    return l;
}

void printLines(line *start) {
    line *current = start;
    while(current != NULL) {
        printf("%s\n", current->text);
        current = current->next;
    }
}

void freeLines(line *start) {
    line *current = start;
    while(current != NULL) {
        line *next = current->next;
        free(current->text);
        free(current);
        current = next;
    }
}

int getPadding(line *l) {
    int count = 0;
    int i = 0;
    while(l->text[i] == ' ') {
        count++;
        i++;
    }
    return count;
}

docNode* lineToDocNode(line *l, int padding) {
    docNode *start = NULL;
    docNode *current = NULL;
    docNode *i = NULL;
    docNode *parentNode = NULL;

    while(l != NULL) {
        int isTyped = 0;
        if(strchr(l->text, '{') && strchr(l->text, '}')) {
            isTyped = 1;
        }

        char *keyDelim = isTyped ? "{" : ":";
        char *key = strtok(l->text, keyDelim) + padding;

        char *type = NULL;
        if(isTyped) {
            type = strtok(NULL, "}");
            if(padding) {
                key[strlen(key) - 1] = '\0';
            }
        }

        char *value = strtok(NULL, "\0");
        if(!value) {
            value = "";
        } else {
            isTyped ? value += 2 : value++;
        }

        i = makeDocNode(key, type, value);
        if(!start) {
            start = i;
            current = i;
        } else {
            current->next = i;
            current = i;
        }

        if(l->next != NULL && getPadding(l) > getPadding(l->next)) {
            break;
        } else if(l->next != NULL && getPadding(l) < getPadding(l->next)) {
            current->children = lineToDocNode(l->next, getPadding(l->next));

            // get pointer to the right place
            do {
                l = l->next;
            }
            while(l->next != NULL && getPadding(l) >= getPadding(l->next));

            if(l->next == NULL) {
                break;
            } else {
                continue;
            }
        }

        l = l->next;
    }
    return start;
}

// docNode

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