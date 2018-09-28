#include <stdio.h>
#include <string.h>

const char delimiter[9] = "--  ====";
const int max_line_length = 100;

int main(int argc, char const *argv[]) {
    if(argc != 2) {
        printf("incorrect input\n\n");
        printf("usage:\n\tsqlDocExtractor <FILE>\n");
    }

    FILE *inputFile = fopen(argv[1], "r");

    char line[max_line_length];
    int isDoc = 0;
    while(fgets(line, max_line_length, inputFile) != NULL) {

        if(isDoc) {
            if(strstr(line, delimiter)) {
                break;
            }
            printf("%s", line + 4);
        }

        if(strstr(line, delimiter)) {
            isDoc = 1;
        }
    }

    fclose(inputFile);
    return 0;
}
