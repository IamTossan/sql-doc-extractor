#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "custom-types.h"

// extractedDoc methods

line* makeLine(char *text) {
    line *l = malloc(sizeof(line));
    l->text = strdup(text);
    l->next = NULL;
    l->text[strlen(l->text) - 1] = '\0';
    return l;
}

void displayLines(line *start) {
    line *current = start;
    while(current != NULL) {
        printf("%s", current->text);
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

docNode* lineToDocNode(line *startLine) {
    docNode *start = NULL;
    docNode *current = NULL;
    docNode *i = NULL;

    line *l = startLine;

    while(l != NULL) {
        char *key = strtok(l->text, ":");
        char *value = (l->text) + strlen(key) + 2;

        i = makeDocNode(key, NULL, value);
        if(!start) {
            start = i;
            current = i;
        } else {
            current->next = i;
            current = i;
        }

        l = l->next;
    }
    return start;
}

// docNode methods

docNode* makeDocNode(char *key, char *type, char *value) {
    docNode *i = malloc(sizeof(docNode));
    i->key = strdup(key);
    i->type = NULL;
    i->value = strdup(value);
    i->children = NULL;
    i->next = NULL;
    return i;
}


void displayDocNode(docNode *start) {
    docNode *current = start;
    while(current != NULL) {
        printf("key: %s, value: %s \n", current->key, current->value);
        current = current->next;
    }
}

void freeDocNode(docNode *start) {
    docNode *current = start;
    while(current != NULL) {
        free(current->key);
        free(current->type);
        free(current->value);
        free(current->children);
        docNode *next = current->next;
        free(current);
        current = next;
    }
}

void toJson(docNode *start) {
    docNode *i = start;

    printf("{");

    while(i != NULL) {
        printf("\n\t\"%s\": \"%s\"", i->key, i->value);
        if(i->next != NULL) {
            printf(",");
        }
        i = i->next;
    }
    printf("\n}\n");
}
