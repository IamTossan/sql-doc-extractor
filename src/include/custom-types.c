#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "custom-types.h"

// extractedDoc methods

int countLineWhiteSpaces(line *l) {
    int count = 0;
    int i = 0;
    while(l->text[i] == ' ') {
        count++;
        i++;
    }
    return count;
}

int countStringWhiteSpace(char *s) {
    int i = 0;
    while(s[i] == ' ') {
        i++;
    }
    return i;
}

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

docNode* lineToDocNode(line *startLine) {
    docNode *start = NULL;
    docNode *current = NULL;
    docNode *i = NULL;
    docNode *parentNode = NULL;

    line *l = startLine;

    while(l != NULL) {
        char *text = strdup(l->text);
        char *key = text + countStringWhiteSpace(strtok(text, ":"));
        char *value = l->text + strlen(key) + countStringWhiteSpace(l->text) + 2;

        i = makeDocNode(key, NULL, value);
        if(!start) {
            start = i;
            current = i;
        } else {
            current->next = i;
            current = i;
        }

        if(l->next != NULL && countLineWhiteSpaces(l) > countLineWhiteSpaces(l->next)) {
            break;
        } else if(l->next != NULL && countLineWhiteSpaces(l) < countLineWhiteSpaces(l->next)) {
            current->children = lineToDocNode(l->next);

            // get pointer to the right place
            do {
                l = l->next;
            }
            while(l->next != NULL && countLineWhiteSpaces(l) >= countLineWhiteSpaces(l->next));

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

// docNode method

docNode* makeDocNode(char *key, char *type, char *value) {
    docNode *i = malloc(sizeof(docNode));
    i->key = key;
    i->type = NULL;
    i->value = value;
    i->children = NULL;
    i->next = NULL;
    return i;
}


void displayDocNode(docNode *start) {
    docNode *current = start;
    while(current != NULL) {
        printf("key: %s\n", current->key);
        if(current->children != NULL) {
            printf("\nchildren of %s:\n\n", current->key);
            displayDocNode(current->children);
        } else {
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

void tabs(int n) {
    for(int i = 0; i < n; i++) {
        printf("\t");
    }
}

void toJson(docNode *start) {
    static int ntabs = 0;
    ntabs++;
    docNode *i = start;

    printf("{\n");

    while(i != NULL) {
        tabs(ntabs);
        printf("\"%s\": ", i->key);
        if(i->children != NULL) {
            toJson(i->children);
        } else {
            printf("\"%s\"", i->value);
        }
        if(i->next != NULL) {
            printf(",\n");
        }
        i = i->next;
    }
    printf("\n");
    tabs(ntabs - 1);
    printf("}");
    ntabs--;
}
