
typedef struct line {
    char *text;
    struct line *next;
} line;

line* makeLine(char *text);

void printLines(line *start);

void freeLines(line *start);

docNode* lineToDocNode(char *line, int padding);

docNode* linesToDocNode(line *startLine, int padding);
