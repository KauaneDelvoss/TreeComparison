#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    FILE *file = fopen("graph/generated/values.txt", "r");
    if (file == NULL) {
        return 1;
    }

    int routine = atoi(argv[1]);

    if (routine == 1) {
        executeInsertionRoutine(file);
    }

    if (routine == 2) {
        executeRemovalRoutine(file);
    }

    printf("%ld\n", comparacoes);

    fclose(file);
    return 0;
}