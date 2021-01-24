#ifndef STRING_LINKED_LIST_H
#define STRING_LINKED_LIST_H

typedef struct line {
    char *text;
    struct line *next;
} line;

line* makeLine(char *text);

void printLines(line *start);

void freeLines(line *start);

docNode* linesToDocNode(line *startLine, int padding);

#endif