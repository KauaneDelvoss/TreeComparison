#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    int order = atoi(argv[1]);
    int routine = atoi(argv[2]);

    FILE* file = fopen("graph/generated/values.txt", "r");
    if (file == NULL) {
        return 1;
    }

    if (routine == 1) {
        executeInsertionRoutine(file, order);
    }

    if (routine == 2) {
        executeRemovalRoutine(file, order);
    }

    printf("%ld\n", comparacoes);

    fclose(file);
    return 0;
}