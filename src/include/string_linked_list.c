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

docNode* lineToDocNode(char *line, int padding) {
    int isTyped = 0;
    if(strchr(line, '{') && strchr(line, '}')) {
        isTyped = 1;
    }

    char *keyDelim = isTyped ? "{" : ":";
    char *key = strtok(line, keyDelim) + padding;

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

    return makeDocNode(key, type, value);
}

docNode* linesToDocNode(line *l, int padding) {
    docNode *start = NULL;
    docNode *current = NULL;

    while(l != NULL) {
        docNode *i = lineToDocNode(l->text, padding);
        if(!start) {
            start = i;
            current = i;
        } else {
            current->next = i;
            current = i;
        }

        if(l->next == NULL || getPadding(l) > getPadding(l->next)) {
            break;
        }

        if(getPadding(l) < getPadding(l->next)) {
            l = l->next;
            current->children = linesToDocNode(l, getPadding(l));

            // get pointer to the right place
            while(l->next != NULL && getPadding(l) >= getPadding(l->next)) {
                l = l->next;
            }

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
