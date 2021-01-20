
// extractedDoc
typedef struct line {
    char *text;
    struct line *next;
} line;

int countWhiteSpaces(line *l);

line* makeLine(char *text);

void displayLines(line *start);

void freeLines(line *start);

//docNode
typedef struct docNode {
    char *key;
    char *type;
    char *value;
    struct docNode *children;
    struct docNode *next;
} docNode;

docNode* makeDocNode(char *key, char *type, char *value);

docNode* lineToDocNode(line *startLine);

void displayDocNode(docNode *start);

void freeDocNode(docNode *start);

void printJson(docNode *start, int padding, int paddingStep);
