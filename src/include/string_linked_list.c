#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "doc_tree.h"
#include "string_linked_list.h"

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
