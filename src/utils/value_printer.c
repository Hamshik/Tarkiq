#include <stdio.h>
#include "value_printer.h"

void print_value(Value value, DataTypes_t datatype) {
    printf("Result: ");
    switch (datatype) {
        case INT:      printf("%d\n", value.inum); break;
        case SHORT:    printf("%hd\n", value.shnum); break;
        case FLOAT:    printf("%f\n", value.fnum); break;
        case DOUBLE:   printf("%g\n", value.lfnum); break;
        case BOOL:     printf("%s\n", value.bval ? "true" : "false"); break;
        case STRINGS:  printf("%s\n", value.str ? value.str : ""); break;
        case CHARACTER:printf("%c\n", value.characters); break;
        default:       printf("<unknown>"); break;
    }
}
