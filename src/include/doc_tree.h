#ifndef DOC_TREE_H
#define DOC_TREE_H

typedef struct docNode {
    char *key;
    char *type;
    char *value;
    struct docNode *children;
    struct docNode *next;
} docNode;

docNode* makeDocNode(char *key, char *type, char *value);

void printDocNode(docNode *start);

void freeDocNode(docNode *start);

void printJson(docNode *start, int padding, int paddingStep);

#endif