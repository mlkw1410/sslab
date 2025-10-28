#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char opcode[15], label[15], operand[15];
    char optab_opcode[15], optab_value[15];
    int locctr, start, length;

    FILE *input, *optab, *symtab, *inter, *leng;

    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "w");
    inter = fopen("intermediate.txt", "w");
    leng = fopen("length.txt", "w");

    if (!input || !optab || !symtab || !inter || !leng) {
        printf("Error in file opening\n");
        return 1;
    }

    fscanf(input, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        locctr = (int)strtol(operand, NULL, 16);
        start = locctr;
        fprintf(inter, "%-8X %-8s %-8s %s\n", locctr, label, opcode, operand);
        fscanf(input, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
        start = 0;
    }

    while (1) {
        if (strcmp(opcode, "END") == 0) {
            fprintf(inter, "%-8X %-8s %-8s %s\n", locctr, label, opcode, operand);
            break;
        }
        
        if (strcmp(label, "~") != 0) {
            fprintf(symtab, "%-8s %-8X\n", label, locctr);
        }

        fprintf(inter, "%-8X %-8s %-8s %s\n", locctr, label, opcode, operand);

        rewind(optab);
        int found = 0;

        while (fscanf(optab, "%s %s", optab_opcode, optab_value) == 2) {
            if (strcmp(opcode, optab_opcode) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (found == 0) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 3 * (strtol(operand, NULL, 10));
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    locctr += strlen(operand) - 3;
                } else if (operand[0] == 'X') {
                    locctr += (strlen(operand) - 3) / 2;
                }
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += strtol(operand, NULL, 10);
            }
        }

        if (fscanf(input, "%s %s %s", label, opcode, operand) != 3) {
            printf("Error reading input file or unexpected end of file\n");
            break;
        }
    }

    length = locctr - start;
    printf("Program length: %X\n", length);
    fprintf(leng, "%X\n", length);

    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(inter);
    fclose(leng);

    return 0;
}

